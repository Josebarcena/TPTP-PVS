thf(general_type, type, general: $tType).
thf(symbol_type, type, symbol: $tType).
thf(f__integer___decl, type, f__integer__: ($int) > general).
thf(f__symbolic___decl, type, f__symbolic__: (symbol) > general).
thf(inf_type, type, c__infimum__: general).
thf(sup_type, type, c__supremum__: general).
thf(p__is_integer__decl, type, p__is_integer__: (general) > $o).
thf(p__is_symbolic__decl, type, p__is_symbolic__: (general) > $o).
thf(p__less_equal__decl, type, p__less_equal__: (general * general) > $o).
thf(p__less__decl, type, p__less__: (general * general) > $o).
thf(p__greater_equal__decl, type, p__greater_equal__: (general * general) > $o).
thf(p__greater__decl, type, p__greater__: (general * general) > $o).


thf(p__is_integer__def_ax, axiom, ![X: general]: (p__is_integer__(X) <=> (?[N: $int]: (X = f__integer__(N))))).
thf(p__is_symbolic__def_ax, axiom, ![X1: general]: (p__is_symbolic__(X1) <=> (?[X2: symbol]: (X1 = f__symbolic__(X2))))).
thf(general_universe_ax, axiom, ![X: general]: ((X = c__infimum__) | p__is_integer__(X) | p__is_symbolic__(X) | (X = c__supremum__))).
thf(f__integer__def_ax, axiom, ![N1: $int, N2: $int]: ((f__integer__(N1) = f__integer__(N2)) <=> (N1 = N2))).
thf(f__symbolic__def_ax, axiom, ![S1: symbol, S2: symbol]: ((f__symbolic__(S1) = f__symbolic__(S2)) <=> (S1 = S2))).
thf(numeral_ordering_ax, axiom, ![N1: $int, N2: $int]: (p__less_equal__(f__integer__(N1), f__integer__(N2)) <=> $lesseq(N1, N2))).
thf(antisymmetric_ordering_ax, axiom, ![X1: general, X2: general]: ((p__less_equal__(X1, X2) & p__less_equal__(X2, X1)) => (X1 = X2))).
thf(transitive_ordering_ax, axiom, ![X1: general, X2: general, X3: general]: ((p__less_equal__(X1, X2) & p__less_equal__(X2, X3)) => p__less_equal__(X1, X3))).
thf(strongly_connected_ordering_ax, axiom, ![X1: general, X2: general]: (p__less_equal__(X1, X2) | p__less_equal__(X2, X1))).
thf(p__less__def_ax, axiom, ![X1: general, X2: general]: (p__less__(X1, X2) <=> (p__less_equal__(X1, X2) & (X1 != X2)))).
thf(p__greater_equal__def_ax, axiom, ![X1: general, X2: general]: (p__greater_equal__(X1, X2) <=> p__less_equal__(X2, X1))).
thf(p__greater__def_ax, axiom, ![X1: general, X2: general]: (p__greater__(X1, X2) <=> (p__less_equal__(X2, X1) & (X1 != X2)))).
thf(minimal_element_ax, axiom, ![N: $int]: p__less__(c__infimum__, f__integer__(N))).
thf(numerals_less_than_symbols_ax, axiom, ![N: $int, S: symbol]: p__less__(f__integer__(N), f__symbolic__(S))).
thf(maximal_element_ax, axiom, ![S: symbol]: p__less__(f__symbolic__(S), c__supremum__)).
thf(predicate_0, type, hq: (general) > $o).
thf(predicate_1, type, tq: (general) > $o).
thf(predicate_2, type, hp: (general) > $o).
thf(predicate_3, type, tp: (general) > $o).
thf(formula_0_transition_axiom_0, axiom, ![X1_g: general]: (hq(X1_g) => tq(X1_g))).

thf(prime_def,definition,
    ! [N: $int,M: $int] :
      ( divides(N,M)
    <=> ? [X: $int] : (  M = ( N  * X  ) ) ) ).

thf(simple_example, axiom, 
    (p & q) => r).

thf(simple_example_wrong, axiom, 
    p & (q => r)).