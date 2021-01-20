
; Problem 1
(define-macro (list-of map-expr for var in lst if filter-expr)
    ;;(list 'map
    ;;    (list 'lambda (list var) map-expr)
    ;;    (list 'filter (list 'lambda (list var) filter-expr) lst)
    ;;)
    `(map (lambda (,var) ,map-expr) (filter (lambda (,var) ,filter-expr) ,lst))
)

; Problem 2
(define (map-stream f s)
    (if (null? s)
    	nil
    	(cons-stream (f (car s)) (map-stream f (cdr-stream s)))))

(define multiples-of-three
  (map-stream (lambda (x) (* 3 x)) ((lambda (x) (define (nats st) (cons-stream st (nats (+ 1 st)))) (nats x)) 1))
)

; Problem 3
(define (rle s)
  (define (helper s cnt)
    (cond
        ((null? s) nil)
        ((null? (cdr-stream s)) (cons-stream (list (car s) (+ 1 cnt)) nil))
        ((= (car (cdr-stream s)) (car s)) (helper (cdr-stream s) (+ 1 cnt)))
        (else (cons-stream (list (car s) (+ 1 cnt)) (helper (cdr-stream s) 0)))
    )
  )
  (helper s 0)
)
