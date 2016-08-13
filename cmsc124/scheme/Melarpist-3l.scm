;;Ferriel Lisandro B. Melarpis
;;2012-01065
;;BS Computer Science
;;University of the Philippines Los Banos
;;Mauritius National Flag Problem Scheme Solution
(display "\x1b[32mSampling\x1b[5m...\x1b[m")
(newline)
; Sample List of Dotted Pairs
(define sampleList1 
    (list (cons 'R 3)
            (cons 'G 6)
            (cons 'Y 1)
            (cons 'B 2)
            (cons 'Y 7) 
            (cons 'G 3)
            (cons 'R 1)
            (cons 'B 8)
    )
)

(define sampleList2 
    (list (cons 'G 4)
            (cons 'R 3)
            (cons 'B 2)
            (cons 'B 6)
            (cons 'B 3)
            (cons 'Y 4)
            (cons 'Y 5)
            (cons 'R 1)
            (cons 'G 3)
    )
)
; end of Sample List

; function for traversing the list and comparing the number element
(define (traverse L)
    (cond
        ((null? L) '())
        ((null? (cdr L)) 
            L
        )
        ((< (cdar L) (cdadr L))
            (cons (car L) (traverse (cdr L)))
        )
        (else
            (cons (cadr L) (traverse (cons (car L) (cddr L))))
        )
    )
)
; end of traverse function

; tail recursive function for sorting number elements
(define (nsort N L)
    (if (<= N 1) (traverse L)
        (nsort (- N 1) (traverse L))
    )
)
; end of number sort function

; tail recursive function for sorting the color elements
(define (csort L r b y g)
    (cond 
        ((null? L) (append (nsort (length r) r) (append (nsort (length b) b) (append (nsort (length y) y) (nsort (length g) g)))))
        ((eq? (caar L) 'R) (csort (cdr L) (cons (car L) r) b y g))
        ((eq? (caar L) 'B) (csort (cdr L) r (cons (car L) b) y g))
        ((eq? (caar L) 'Y) (csort (cdr L) r b (cons (car L) y)  g))
        ((eq? (caar L) 'G) (csort (cdr L) r b y (cons (car L) g)))
    )
)
; end of color sort function

; function for sorting a list of dotted pairs of a color and a number
(define (MauritiusSort L)
    (csort L '() '() '() '())
)
; end of MauritiusSort

(display "\x1b[33msampleList1 \x1b[5m:\x1b[m \x1b[36m")
(display sampleList1)
(newline)
(display "\x1b[34mSorted List \x1b[5m:\x1b[m \x1b[35m\x1b[4m")
(display (MauritiusSort sampleList1))
(newline)
(display "\x1b[m\x1b[33msampleList2 \x1b[5m:\x1b[m \x1b[36m")
(display sampleList2)
(newline)
(display "\x1b[34mSorted List \x1b[5m:\x1b[m \x1b[35m\x1b[4m")
(display (MauritiusSort sampleList2))
(newline)
(display "\x1b[m\x1b[32mDONE.\x1b[m")
(newline)
