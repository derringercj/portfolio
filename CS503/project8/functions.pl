/* Our functions we want to define to return the count of employees given a certain condition, as well as min, max, total, and avg of employee salaries given certain conditions */

list('==', Ref, List) :- findall([X, Y, Z], (pay(X, Y, Z), Z =:= Ref), List).
list('!=', Ref, List) :- findall([X, Y, Z], (pay(X, Y, Z), Z =\= Ref), List).
list('>', Ref, List) :- findall([X, Y, Z], (pay(X, Y, Z), Z > Ref), List).
list('>=', Ref, List) :- findall([X, Y, Z], (pay(X, Y, Z), Z >= Ref), List).
list('<', Ref, List) :- findall([X, Y, Z], (pay(X, Y, Z), Z < Ref), List).
list('<=', Ref, List) :- findall([X, Y, Z], (pay(X, Y, Z), Z =< Ref), List).

count('==', Ref, Count) :- findall(Z, (pay(_, _, Z), Z =:= Ref), List), length(List, Count).
count('!=', Ref, Count) :- findall(Z, (pay(_, _, Z), Z =\= Ref), List), length(List, Count).
count('>', Ref, Count) :- findall(Z, (pay(_, _, Z), Z > Ref), List), length(List, Count).
count('>=', Ref, Count) :- findall(Z, (pay(_, _, Z), Z >= Ref), List), length(List, Count).
count('<', Ref, Count) :- findall(Z, (pay(_, _, Z), Z < Ref), List), length(List, Count).
count('<=', Ref, Count) :- findall(Z, (pay(_, _, Z), Z =< Ref), List), length(List, Count).

min('==', Ref, Min) :- findall(Z, (pay(_, _, Z), Z =:= Ref), List), min_list(List, Min).
min('!=', Ref, Min) :- findall(Z, (pay(_, _, Z), Z =\= Ref), List), min_list(List, Min).
min('>', Ref, Min) :- findall(Z, (pay(_, _, Z), Z > Ref), List), min_list(List, Min).
min('>=', Ref, Min) :- findall(Z, (pay(_, _, Z), Z >= Ref), List), min_list(List, Min).
min('<', Ref, Min) :- findall(Z, (pay(_, _, Z), Z < Ref), List), min_list(List, Min).
min('<=', Ref, Min) :- findall(Z, (pay(_, _, Z), Z =< Ref), List), min_list(List, Min).

max('==', Ref, Max) :- findall(Z, (pay(_, _, Z), Z =:= Ref), List), max_list(List, Max).
max('!=', Ref, Max) :- findall(Z, (pay(_, _, Z), Z =\= Ref), List), max_list(List, Max).
max('>', Ref, Max) :- findall(Z, (pay(_, _, Z), Z > Ref), List), max_list(List, Max).
max('>=', Ref, Max) :- findall(Z, (pay(_, _, Z), Z >= Ref), List), max_list(List, Max).
max('<', Ref, Max) :- findall(Z, (pay(_, _, Z), Z < Ref), List), max_list(List, Max).
max('<=', Ref, Max) :- findall(Z, (pay(_, _, Z), Z =< Ref), List), max_list(List, Max).

total('==', Ref, Total) :- findall(Z, (pay(_, _, Z), Z =:= Ref), List), sum_list(List, Total).
total('!=', Ref, Total) :- findall(Z, (pay(_, _, Z), Z =\= Ref), List), sum_list(List, Total).
total('>', Ref, Total) :- findall(Z, (pay(_, _, Z), Z > Ref), List), sum_list(List, Total).
total('>=', Ref, Total) :- findall(Z, (pay(_, _, Z), Z >= Ref), List), sum_list(List, Total).
total('<', Ref, Total) :- findall(Z, (pay(_, _, Z), Z < Ref), List), sum_list(List, Total).
total('<=', Ref, Total) :- findall(Z, (pay(_, _, Z), Z =< Ref), List), sum_list(List, Total).

avg('==', Ref, Avg) :- findall(Z, (pay(_, _, Z), Z =:= Ref), List), sum_list(List, Total), length(List, Count), Avg is Total / Count.
avg('!=', Ref, Avg) :- findall(Z, (pay(_, _, Z), Z =\= Ref), List), sum_list(List, Total), length(List, Count), Avg is Total / Count.
avg('>', Ref, Avg) :- findall(Z, (pay(_, _, Z), Z > Ref), List), sum_list(List, Total), length(List, Count), Avg is Total / Count.
avg('>=', Ref, Avg) :- findall(Z, (pay(_, _, Z), Z >= Ref), List), sum_list(List, Total), length(List, Count), Avg is Total / Count.
avg('<', Ref, Avg) :- findall(Z, (pay(_, _, Z), Z < Ref), List), sum_list(List, Total), length(List, Count), Avg is Total / Count.
avg('<=', Ref, Avg) :- findall(Z, (pay(_, _, Z), Z =< Ref), List), sum_list(List, Total), length(List, Count), Avg is Total / Count.