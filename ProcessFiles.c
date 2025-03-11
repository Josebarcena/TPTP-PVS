#include <dirent.h>
#include "Threads.c"

int running = 1;


void ReadDir(char *folder){
    struct dirent *de;
    char fullPath[2048 + strlen(folder)];
    DIR *dr = opendir(fullPath);

    if(dr == NULL){
        perror("ERROR: Directory cant be opened.\n");
        exit(EXIT_FAILURE);
    }

    while ((de = readdir(dr)) != NULL){ // we send each file != . | ..
        if(de->d_type == DT_REG){
            snprintf(fullPath, sizeof(fullPath), "%s/%s", folder, de->d_name);        
            addTask(fullPath);
        }
        else if(de->d_type == DT_DIR){
            snprintf(fullPath, sizeof(fullPath), "%s/%s", folder, de->d_name);
            ReadDir(fullPath);
        }
    }
    running = 0;
    closedir(dr);
}

//Function to parse each file
void *ProcessFile(){
    char task[PATH_MAX];
    while(running) {
        pthread_mutex_lock(&queue_mutex);
        while (taskCount == 0) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
            
        }
        strcpy(task,GetTask());
        pthread_mutex_unlock(&queue_mutex);
        Processing(task, pthread_self());
    }
    return NULL;
}

void Processing(char * file,int numThread){
    if (stat("Output", &st) == -1) {
        printf("Creating Output Directory...\n");
        if (mkdir("Output", 0700) == -1) {
            perror("ERROR: Cant create 'Output'");
            exit(EXIT_FAILURE);
        }
    }

   FILE *in = fopen(file, "r");
        if (in == NULL) {
            printf("ERROR: File cant be opened.\r\n");
            exit(EXIT_FAILURE);
        }
        else {
            char *baseName = strrchr(file, FILE_SEPARATOR);
            if (baseName) {
                baseName++;
            } else {
                baseName = file;
            }
            outputFileName = malloc(strlen(baseName) + 15);
            snprintf(outputFileName,strlen(baseName) + 15, "Output%c%s.pvs", FILE_SEPARATOR, baseName);
            fileName[numThread] = strdup(baseName);
            //printf("Creating FILE : %s \n", outputFileName);
            outputFile = fopen(outputFileName, "w");

            if (outputFile == NULL) {
                perror("ERROR: OutputFile cant be created.\n");
                fclose(in);
                free(outputFileName);
                free(data);
                exit(EXIT_FAILURE);
            }
            head[numThread] = NULL;
            auxComment[numThread] = NULL;
            aux[numThread] = NULL;

            yyscan_t scanner;
            yylex_init(&scanner);
            yyset_out(outputFile, scanner);
            yyset_in(in, scanner);
            yyparse(scanner, data->numThread);

            fclose(outputFile);
            fclose(in);

            yylex_destroy(scanner);
        }
    
    RunPythonScript(outputFileName);
    free(outputFileName);
    pthread_exit(NULL);

} 