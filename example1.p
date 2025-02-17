%--------- EJEMPLO1 DE TPTP ---------
/* TRADUCCION TEOR_NUM_BASICO.PVS -------
--------- AUTHOR: xxxx ----------------*/
thf(divides, definition,
    ! [N: $int, M: $int] :
        ( divides(N, M) 
        <=> ? [X: $int] : (M = (N * X)) ) ).

%----- NO SE DEBERIA MOSTRAR
thf(prime_def,definition,
    ! [N: $int,M: $int] :
      ( divides(N,M)
    <=> ? [X: $int] : (  M = ( N  * X  ) ) ) ).

thf(eq_mod, definition,
    ! [P: $int, N: $int, M: $int] :
        ( eq_mod(P, N, M) 
        <=> ? [L: $int] : (M = ((L * P) + N)) ) ).

thf(divides_32_imp_4, conjecture,
    ! [X: $int] :
        ( divides(32, X) => divides(4, X) ) ).

thf(divides_sum, conjecture,
    ! [X: $int, N: $int, M: $int] :
        (( divides(X, N) & divides(X, M)) => (divides(X, (N + M))) ) ).

thf(divides_opposite, conjecture,
    ! [X: $int, N: $int] :
        ( divides(X, -N) <=> divides(X, N) ) ).

thf(opposite_divides, conjecture,
    ! [X: $int, N: $int] :
        ( divides(-X, N) <=> divides(X, N) ) ).

thf(divides_prod1, conjecture,
    ! [X: $int, N: $int, M: $int] :
        ( divides(X, N) => divides(X, (N * M)) ) ).

thf(divides_prod2, conjecture,
    ! [X: $int, N: $int, M: $int] :
        ( divides(X, N) => divides(X, (M * N)) ) ).

thf(divides_sum_prod, conjecture,
    ! [X: $int, N: $int, M: $int, L: $int, Y: $int] :
        (( divides(X, N) & divides(X, M)) => (divides(X, ((N * L) + (M * Y)))) ) ).

thf(divides_prod_elim1, conjecture,
    ! [NZ: $int, N: $int, M: $int] :
        ( divides((NZ * N), (NZ * M)) <=> divides(N, M) ) ).

thf(divides_prod_elim2, conjecture,
    ! [NZ: $int, N: $int, M: $int] :
        ( divides((N * NZ), (M * NZ)) <=> divides(N, M) ) ).

thf(divides_Barja1, conjecture,
    ! [N: $int, M: $int] :
        ( divides(7, ((10 * N) + M)) <=> divides(7, (N + (5 * M))) ) ).
