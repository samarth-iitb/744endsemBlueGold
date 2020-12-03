# 744endsemBlueGold

This is a PoC for the Blue and Gold lock question. It shows that blue acquisitions are given preference over gold acquisitions even if we use a single condition variable and broadcast the request while releasing the lock.

## Compilation
```
make
```

## Execution

```
make run
```

By default 5 Blue and 5 Gold requests are issued concurrently and we can observe that gold requests are only granted once all the blue requests are granted. 

##### Sample Output

```
Blue acquired lock
Blue acquired lock
Blue acquired lock
Blue acquired lock
Blue acquired lock
Gold acquired lock
Gold acquired lock
Gold acquired lock
Gold acquired lock
Gold acquired lock
```