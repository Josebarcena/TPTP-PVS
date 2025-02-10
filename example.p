%------------------------------------------------------------------------------
thf(beverage_decl,type,beverage: $tType).
thf(syrup_decl,type,syrup: $tType).
thf(coffee_decl,type,coffee: beverage).
thf(mix_decl,type,mix: beverage > syrup > beverage).
thf(heat_decl,type,heat: beverage > beverage ).
thf(heated_mix_decl,type,heated_mix: beverage > syrup > beverage).
thf(hot_decl,type,hot: beverage > $o).

thf(heated_mix,axiom,
    heated_mix = ( ^ [B: beverage,S :syrup] : ( heat @ ( mix @ B @ S ))) ).

thf(hot_mixture,axiom,
    ! [B: beverage,S: syrup] : ( hot @ ( heated_mix @ B @ S ) ) ).

thf(heated_coffee_mix,axiom,
    ! [S: syrup] : ( ( heated_mix @ coffee @ S ) = coffee ) ).

thf(hot_coffee,conjecture,
    ? [Mixture: syrup > beverage] :
    ! [S: syrup] :
        ( ( ( Mixture @ S ) = coffee )
        & ( hot @ ( Mixture @ S ) ) ) ).
%------------------------------------------------------------------------------

%------------------------------------------------------------------------------
thf(prime_def,definition,
    ! [N: $int,M: $int] :
      ( divides(N,M)
    <=> ? [X: $int] : (  M = ( N  * X  ) ) ) ).
%------------------------------------------------------------------------------