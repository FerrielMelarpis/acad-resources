;##########Insertion Sort##################
;Function to insert an element into a sorted list
(define (insert-into L e)
  (if (null? L)
      (list e)
      (if (< e (car L))
   (cons e L)
   (cons (car L) (insert-into (cdr L) e))
      )
  )

)

;This function keeps on adding each element of the list to 'new-L' which will be a sorted list
(define (insertion-sort2 L new-L)
      (if (null? L)
   new-L
   (insertion-sort2 (cdr L) (insert-into new-L (car L)))
      )

)

(define (insertion-sort L)
   (if (or (null? L) (null? (cdr L)))
 L
 (insertion-sort2 L '())
   )
)

(define (bubble-up L)  
   (if (null? (cdr L))  
     L   
  (if (< (car L) (cadr L))  
(cons (car L) (bubble-up (cdr L)))  
(cons (cadr L) (bubble-up (cons (car L) (cddr L))))  
  )
 )  

(define (bubbleSort n l)
    (cond ((= n 1) (bubble-up l))
        (else (bubbleSort (- n 1) (bubble-up l)))
    )
)