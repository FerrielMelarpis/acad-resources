; factorial
(define (fact n)
       (if (< n 2)
       1
       (* n (fact (- n 1)))
       )
)
; factorial with accumulator
(define (fact2 n a)
       (if (= n 0)
       a
       (fact2 (- n 1) (* n a)))
)
; list_reverse
(define (rev l)
       (if (null? l)
       '()
       (append (rev (cdr l))
              (list (car l))))
)
; list_reverse with accumulator
(define (rev2 l r)
       (if (null? l)
       r
       (rev2 (cdr l)
              (cons (car l) r)))
)
; fibbonacci
(define (fib n)
       (if (< n 3)
       1
       (+ (fib (- n 1)) (fib (- n 2))))
)
; fibonacci with accumulator
(define (fib2 n a b)
       (cond
       ((< n 1) a)
       ((= n 1) b)
       (else (fib2 (- n 1) b (+ a b))))
)
; sort list of numbers
(define (nsort L)
    (cond
        ((null? (cdr L)) 
            L
        )
        ((> (car L) (cadr L))
            (cons (car L) (nsort (cdr L)))
        )
        (else
            (cons (cadr L) (nsort (cons (car L) (cddr L))))
        )
    )
)
(define (bsort N L)
    (cond 
        ((= N 1)
            (nsort L)
        )
        (else
            (bsort (- N 1) (nsort L))
        )
    )
)

(display "\x1b[32mStart of Program\x1b[m")
(newline)
(display "\x1b[35m5! = \x1b[36m")
(display (fact2 5 1))
(newline)
(display "\x1b[35m5th fibonacci number: \x1b[36m")
(display (fib2 5 0 1))
(newline)
(display "\x1b[35mSorted Number List (5 2 3 1 4) => \x1b[36m")
(display (bsort 5 '(5 2 3 1 4)))
(newline)
