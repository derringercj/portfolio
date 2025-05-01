/* Rules that help us calculate the pay of the employees given in our facts file */

pay(First, Last, P) :- salaried(First, Last, Salary), P is Salary.

pay(First, Last, P) :- hourly(First, Last, Hours, Rate),
                        Hours > 50,
                        P is (((Hours - 50) * (Rate * 2)) + (10 * (Rate * 1.5)) + (40 * Rate)).

pay(First, Last, P) :- hourly(First, Last, Hours, Rate),
                        Hours > 40, Hours =< 50,
                        P is (((Hours - 40) * (Rate * 1.5)) + (40 * Rate)).

pay(First, Last, P) :- hourly(First, Last, Hours, Rate),
                        Hours =< 40, 
                        P is (Hours * Rate).

pay(First, Last, P) :- commission(First, Last, Min, Sales, Crate),
                        Sales * Crate > Min,
                        P is Sales * Crate.

pay(First, Last, P) :- commission(First, Last, Min, Sales, Crate),
                        Sales * Crate =< Min,
                        P is Min.