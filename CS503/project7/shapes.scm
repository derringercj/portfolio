(define (perform command filename . args) 
    (if (not(zero? (remainder (length args) 3))) ; If number of arguments is not divisible by 3
        (begin
            (newline) (display "Incorrect number of arguments.")
            'done)
    (begin  ; Otherwise
        (if(file-exists? filename) ; If file exists
            (begin
                (let ((port (open-input-file filename))) ; Open it
                ; Get list of lists where each element denotes the shapes
                (define shapes-list (read-shapes port))

                (cond 
                    ((string=? command "count") (count shapes-list args))
                    ((string=? command "print") (print shapes-list args))
                    ((string=? command "min") (mini shapes-list args))
                    ((string=? command "max") (maxi shapes-list args))
                    ((string=? command "total") (total shapes-list args))
                    ((string=? command "avg") (avg shapes-list args))
                )
                (close-input-port port)
            ))
            (begin ; Otherwise print errors
                (newline) (display "Unable to open file ")
                (display filename)
                (display " for reading")
            ))
        'done)))

; Function that reads the lines of the file and stores them in strings-list, then splits the strings into their own list, creating a list of lists
(define (read-shapes port)
  (let* ((strings-list (read-lines port))
         (shapes-list (map (lambda (line) (string-split char-whitespace? line)) strings-list)))
    shapes-list))

; Split a string over a given delimiter
(define (string-split char-delimiter? string)
  (define (maybe-add a b parts)
    (if (= a b) parts (cons (substring string a b) parts)))
  (let ((n (string-length string)))
    (let loop ((a 0) (b 0) (parts '()))
      (if (< b n)
          (if (not (char-delimiter? (string-ref string b)))
              (loop a (+ b 1) parts)
              (loop (+ b 1) (+ b 1) (maybe-add a b parts)))
          (reverse (maybe-add a b parts))))))

; This function reads our file line by line and builds a list of strings, each line of the file
(define (read-lines port)
    (let ((stuff (read-line port)))
        (if (eof-object? stuff)
    '()
    (begin
        (cons stuff (read-lines port))))))

; Function that compares our shape type to a given type based on our passed operator
(define (evaluate-type shape op given-type)
    (let ((shape-type (cadr shape)))
        (cond
            ((string=? op "==") (string=? shape-type given-type))
            ((string=? op "!=") (not(string=? shape-type given-type)))
            ((string=? op ">=") (string>=? shape-type given-type))
            ((string=? op "<=") (string<=? shape-type given-type))
            ((string=? op ">") (string>? shape-type given-type))
            ((string=? op "<") (string<? shape-type given-type)))))

; Function that calls appropriate shape area calculation and returns truth value of our shape area in comparison to passed value
(define (evaluate-area shape op value)
    (let ((shape-type (cadr shape)))
        (cond
            ((string=? shape-type "box") 
                (cond 
                    ((string=? op "==") (= (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))
                    ((string=? op "!=") (not(= (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value)))
                    ((string=? op ">=") (>= (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))
                    ((string=? op "<=") (<= (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))
                    ((string=? op ">") (> (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))
                    ((string=? op "<") (< (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))))
            ((string=? shape-type "cylinder") 
                (cond
                    ((string=? op "==") (= (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "!=") (not(= (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape))) value)))
                    ((string=? op ">=") (>= (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "<=") (<= (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op ">") (> (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "<") (< (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape))) value))))
            ((string=? shape-type "sphere") 
                (cond
                    ((string=? op "==") (= (calculate-sphere-area (string->number(caddr shape))) value))
                    ((string=? op "!=") (not(= (calculate-sphere-area (string->number(caddr shape))) value)))
                    ((string=? op ">=") (>= (calculate-sphere-area (string->number(caddr shape))) value))
                    ((string=? op "<=") (<= (calculate-sphere-area (string->number(caddr shape))) value))
                    ((string=? op ">") (> (calculate-sphere-area (string->number(caddr shape))) value))
                    ((string=? op "<") (< (calculate-sphere-area (string->number(caddr shape))) value))))
            ((string=? shape-type "torus") 
                (cond
                    ((string=? op "==") (= (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "!=") (not(= (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape))) value)))    
                    ((string=? op ">=") (>= (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "<=") (<= (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op ">") (> (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "<") (< (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape))) value)))))))

; Function that calls appropriate shape volume calculation and returns truth value of our shape volume in comparison to passed value
(define (evaluate-volume shape op value)
    (let ((shape-type (cadr shape)))
        (cond
            ((string=? shape-type "box") 
                (cond 
                    ((string=? op "==") (= (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))
                    ((string=? op "!=") (not(= (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value)))
                    ((string=? op ">=") (>= (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))
                    ((string=? op "<=") (<= (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))
                    ((string=? op ">") (> (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))
                    ((string=? op "<") (< (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) value))))
            ((string=? shape-type "cylinder") 
                (cond
                    ((string=? op "==") (= (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "!=") (not(= (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))) value)))
                    ((string=? op ">=") (>= (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "<=") (<= (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op ">") (> (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "<") (< (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))) value))))
            ((string=? shape-type "sphere") 
                (cond
                    ((string=? op "==") (= (calculate-sphere-volume (string->number(caddr shape))) value))
                    ((string=? op "!=") (not(= (calculate-sphere-volume (string->number(caddr shape))) value)))
                    ((string=? op ">=") (>= (calculate-sphere-volume (string->number(caddr shape))) value))
                    ((string=? op "<=") (<= (calculate-sphere-volume (string->number(caddr shape))) value))
                    ((string=? op ">") (> (calculate-sphere-volume (string->number(caddr shape))) value))
                    ((string=? op "<") (< (calculate-sphere-volume (string->number(caddr shape))) value))))
            ((string=? shape-type "torus") 
                (cond
                    ((string=? op "==") (= (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "!=") (not(= (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))) value)))    
                    ((string=? op ">=") (>= (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "<=") (<= (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape)))value))
                    ((string=? op ">") (> (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))) value))
                    ((string=? op "<") (< (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))) value)))))))

; Functions that calculate the area of our various possible shapes
(define (calculate-box-area len width height)
    (+ (* 2 len width) (* 2 len height) (* 2 width height)))

(define (calculate-cylinder-area radius height)
    (+ (* 2 3.1415926535 radius height) (* 2 3.1415926535 radius radius)))

(define (calculate-sphere-area radius)
    (* 4 3.1415926535 radius radius))

(define (calculate-torus-area small-radius big-radius)
    (* (* 2 3.1415926535 big-radius) (* 2 3.1415926535 small-radius)))

; Functions that calculate the volume of our various possible shapes
(define (calculate-box-volume len width height)
    (* len width height))

(define (calculate-cylinder-volume radius height)
    (* 3.1415926535 radius radius height))

(define (calculate-sphere-volume radius)
    (* (/ 4 3) 3.1415926535 radius radius radius))

(define (calculate-torus-volume small-radius big-radius)
    (* (* 3.1415926535 small-radius small-radius) (* 2 3.1415926535 big-radius)))

; Function to take out list of conditions and group them into their triplets
(define (group-conditions conditions)
    (if (null? conditions)
        '()
        (cons (list (car conditions) (cadr conditions) (caddr conditions))
            (group-conditions (cdddr conditions)))))

; Function for count command
(define (count shapes conditions)
    ; Checking if there are conditions
    (if (null? conditions)
        ; If there are no conditions, just print the length of the shapes list
        (begin
            (newline)
            (display "There are ")
            (display (length shapes))
            (display " shapes.")
            'done)
        ; Otherwise, evaluate each shape according to the conditions, and if satisfied, increment a counter then display counter
        (begin
            (let ((condition-triplets (group-conditions conditions))
                    (num-satisfying 0))
                ; For each shape in our shape list
                (for-each (lambda (shape)
                    (let ((passed-count 0))
                    ; For each condition in our conditions list
                    (for-each (lambda (current-condition)
                        (let ((cond-type (car current-condition))
                                (operator (cadr current-condition))
                                (threshold (caddr current-condition)))                
                        ; Call proper evaluator function based on the condition we are evaluating
                        (if  (cond
                                ((string=? cond-type "type") (evaluate-type shape operator threshold))
                                ((string=? cond-type "area")(evaluate-area shape operator threshold))
                                ((string=? cond-type "volume")(evaluate-volume shape operator threshold))
                                (else #f)) 
                            ; If shape fits the condition, increment our condition counter
                            (set! passed-count (+ passed-count 1)))))
                        condition-triplets)
                        ; If our shape fits ALL conditions, increment our shape counter
                        (if (= passed-count (length condition-triplets))
                            (set! num-satisfying (+ num-satisfying 1)))))
                shapes)
        ; Display shapes fitting criteria
        (newline)
        (display "There are ")
        (display num-satisfying)
        (display " shapes.")
        'done))))

; Function for print command
(define (print shapes conditions)
    ; Evaluate each shape according to the conditions, and if satisfied, print relevant info
    (let ((condition-triplets (group-conditions conditions))
            (num-satisfying 0))
        ; For each shape in our shapes list
        (for-each (lambda (shape)
            (let ((passed-count 0))
            ; For each condition in our conditions list
            (for-each (lambda (current-condition)
                (let ((cond-type (car current-condition))
                        (operator (cadr current-condition))
                        (threshold (caddr current-condition)))                
                ; Call proper evaluator function based on the condition we are evaluating
                (if  (cond
                        ((string=? cond-type "type") (evaluate-type shape operator threshold))
                        ((string=? cond-type "area")(evaluate-area shape operator threshold))
                        ((string=? cond-type "volume")(evaluate-volume shape operator threshold))
                        (else #f)) 
                    ; If shape fits the condition, increment our condition counter
                    (set! passed-count (+ passed-count 1)))))
                condition-triplets)
        
                ; If our shape fits all conditions, print relevant information on shape
                (if (= passed-count (length condition-triplets))
                    (let ((shape-type (cadr shape)))
                        (cond
                            ((string=? shape-type "box") 
                                (newline)
                                (display "Box: ") (display (car shape)) (display ", Length=") (display (caddr shape)) (display ", Width=") (display (cadddr shape))
                                (display ", Height=") (display (car(cddddr shape))) (newline) (display "\tSurface Area: ") 
                                (display (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape))))) 
                                (display ", Volume: ") (display (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))))
                                (newline))
                            ((string=? shape-type "cylinder") 
                                (newline)
                                (display "Cylinder: ") (display (car shape)) (display ", Radius=") (display (caddr shape)) (display ", Height=") (display (cadddr shape))
                                (newline) (display "\tSurface Area: ") (display (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape))))
                                (display ", Volume: ") (display (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))))
                                (newline))
                            ((string=? shape-type "sphere")
                                (newline)
                                (display "Sphere: ") (display (car shape)) (display ", Radius=") (display (caddr shape)) (newline)
                                (display "\tSurface Area: ") (display (calculate-sphere-area (string->number(caddr shape))))
                                (display ", Volume: ") (display (calculate-sphere-volume (string->number(caddr shape))))
                                (newline))
                            ((string=? shape-type "torus")
                                (newline)
                                (display "Torus: ") (display (car shape)) (display ", Small Radius=") (display (caddr shape)) (display ", Big Radius=") (display (cadddr shape))
                                (newline) (display "\tSurface Area: ") (display (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape))))
                                (display ", Volume: ") (display (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))))
                                (newline)))))))
        shapes)
    'done))
; Function for min command
(define (mini shapes conditions)
    (let ((condition-triplets (group-conditions conditions))
            (num-satisfying 0) (min-area 10000000) (min-volume 10000000))
        ; For each shape in shapes list
        (for-each (lambda (shape)
            (let ((passed-count 0))
            ; For each condition in conditions list
            (for-each (lambda (current-condition)
                (let ((cond-type (car current-condition))
                        (operator (cadr current-condition))
                        (threshold (caddr current-condition)))                
                ; Call appropriate evaluator function based on condition
                (if  (cond
                        ((string=? cond-type "type") (evaluate-type shape operator threshold))
                        ((string=? cond-type "area")(evaluate-area shape operator threshold))
                        ((string=? cond-type "volume")(evaluate-volume shape operator threshold))
                        (else #f)) 
                    ; If shape fits condition, then increment counter
                    (set! passed-count (+ passed-count 1)))))
                condition-triplets)
                ; If shape fits ALL conditions, check if its volume/area is less than our current min, and update it if so
                (if (= passed-count (length condition-triplets))
                    (cond
                        ((string=? (cadr shape) "box") 
                            (if (< (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) min-area)
                                (set! min-area (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape))))))
                            (if (< (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) min-volume)
                                (set! min-volume (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))))))
                        ((string=? (cadr shape) "cylinder") 
                            (if (< (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape))) min-area)
                                (set! min-area (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape)))))
                            (if (< (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))) min-volume)
                                (set! min-volume (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))))))
                        ((string=? (cadr shape) "sphere") 
                            (if (< (calculate-sphere-area (string->number(caddr shape))) min-area)
                                (set! min-area (calculate-sphere-area (string->number(caddr shape)))))
                            (if (< (calculate-sphere-volume (string->number(caddr shape))) min-volume)
                                (set! min-volume (calculate-sphere-volume (string->number(caddr shape))))))
                        ((string=? (cadr shape) "torus") 
                            (if (< (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape))) min-area)
                                (set! min-area (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape)))))
                            (if (< (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))) min-volume)
                                (set! min-volume (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))))))))))
        shapes)
    ; Display min surface area and volume among all qualifying shapes
    (newline)
    (display "min(Surface Area)=") (display min-area) (newline)
    (display "min(Volume)=") (display min-volume) (newline)
    'done))

; Function for max command
(define (maxi shapes conditions)
    (let ((condition-triplets (group-conditions conditions))
            (num-satisfying 0) (max-area 0) (max-volume 0))
        ; For each shape in shapes list
        (for-each (lambda (shape)
            (let ((passed-count 0))
            ; For each condition in conditions list
            (for-each (lambda (current-condition)
                (let ((cond-type (car current-condition))
                        (operator (cadr current-condition))
                        (threshold (caddr current-condition)))                
                ; Call appropriate evaluator function based on condition type
                (if  (cond
                        ((string=? cond-type "type") (evaluate-type shape operator threshold))
                        ((string=? cond-type "area")(evaluate-area shape operator threshold))
                        ((string=? cond-type "volume")(evaluate-volume shape operator threshold))
                        (else #f)) 
                    ; If shape fits condition, increment counter
                    (set! passed-count (+ passed-count 1)))))
                condition-triplets)
        
                ; If shape passes all conditions, check if its volume/area is greater than our current max, and update it if so
                (if (= passed-count (length condition-triplets))
                    (cond
                        ((string=? (cadr shape) "box") 
                            (if (> (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) max-area)
                                (set! max-area (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape))))))
                            (if (> (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))) max-volume)
                                (set! max-volume (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))))))
                        ((string=? (cadr shape) "cylinder") 
                            (if (> (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape))) max-area)
                                (set! max-area (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape)))))
                            (if (> (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))) max-volume)
                                (set! max-volume (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))))))
                        ((string=? (cadr shape) "sphere") 
                            (if (> (calculate-sphere-area (string->number(caddr shape))) max-area)
                                (set! max-area (calculate-sphere-area (string->number(caddr shape)))))
                            (if (> (calculate-sphere-volume (string->number(caddr shape))) max-volume)
                                (set! max-volume (calculate-sphere-volume (string->number(caddr shape))))))
                        ((string=? (cadr shape) "torus") 
                            (if (> (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape))) max-area)
                                (set! max-area (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape)))))
                            (if (> (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))) max-volume)
                                (set! max-volume (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))))))))))
        shapes)
    ; Display max surface area and volume of qualifying shapes
    (newline)
    (display "max(Surface Area)=") (display max-area) (newline)
    (display "max(Volume)=") (display max-volume) (newline)
    'done))
; Function for total command
(define (total shapes conditions)
    (let ((condition-triplets (group-conditions conditions))
            (num-satisfying 0) (total-area 0) (total-volume 0))
        ; For each shape in shapes list
        (for-each (lambda (shape)
            (let ((passed-count 0))
            ; For each condition in conditions list
            (for-each (lambda (current-condition)
                (let ((cond-type (car current-condition))
                        (operator (cadr current-condition))
                        (threshold (caddr current-condition)))                
                ; Calling appropriate evaluator function based on condition
                (if  (cond
                        ((string=? cond-type "type") (evaluate-type shape operator threshold))
                        ((string=? cond-type "area")(evaluate-area shape operator threshold))
                        ((string=? cond-type "volume")(evaluate-volume shape operator threshold))
                        (else #f)) 
                    ; If shape fits condition, increment counter
                    (set! passed-count (+ passed-count 1)))))
                condition-triplets)
                ; If shape fits ALL conditions, add its surface area and volume to our total variables
                (if (= passed-count (length condition-triplets))
                    (cond
                        ((string=? (cadr shape) "box") 
                            (set! total-area (+ total-area (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape))))))
                            (set! total-volume (+ total-volume (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))))))
                        ((string=? (cadr shape) "cylinder") 
                            (set! total-area (+ total-area (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape)))))
                            (set! total-volume (+ total-volume (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))))))
                        ((string=? (cadr shape) "sphere") 
                            (set! total-area (+ total-area (calculate-sphere-area (string->number(caddr shape)))))
                            (set! total-volume (+ total-volume (calculate-sphere-volume (string->number(caddr shape))))))
                        ((string=? (cadr shape) "torus") 
                            (set! total-area (+ total-area (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape)))))
                            (set! total-volume (+ total-volume (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape))))))))))
        shapes)
    ; Display total surface area and volume of qualifying shapes
    (newline)
    (display "total(Surface Area)=") (display total-area) (newline)
    (display "total(Volume)=") (display total-volume) (newline)
    'done))
; Function for avg command
(define (avg shapes conditions)
    (let ((condition-triplets (group-conditions conditions))
            (num-satisfying 0) (total-area 0) (total-volume 0))
        ; For each shape in shapes list
        (for-each (lambda (shape)
            (let ((passed-count 0))
            ; For each condition in conditions list
            (for-each (lambda (current-condition)
                (let ((cond-type (car current-condition))
                        (operator (cadr current-condition))
                        (threshold (caddr current-condition)))                
                ; Call appropriate evaluator function based on condition
                (if  (cond
                        ((string=? cond-type "type") (evaluate-type shape operator threshold))
                        ((string=? cond-type "area")(evaluate-area shape operator threshold))
                        ((string=? cond-type "volume")(evaluate-volume shape operator threshold))
                        (else #f)) 
                    ; If shape fits condition, increment counter
                    (set! passed-count (+ passed-count 1)))))
                condition-triplets)
                ; If shape fits all conditions, add surface area and volume to our total variables
                (if (= passed-count (length condition-triplets))
                    (begin
                        (set! num-satisfying (+ num-satisfying 1))
                        (cond
                            ((string=? (cadr shape) "box") 
                                (set! total-area (+ total-area (calculate-box-area (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape))))))
                                (set! total-volume (+ total-volume (calculate-box-volume (string->number(caddr shape)) (string->number(cadddr shape)) (string->number(car (cddddr shape)))))))
                            ((string=? (cadr shape) "cylinder") 
                                (set! total-area (+ total-area (calculate-cylinder-area (string->number(caddr shape)) (string->number(cadddr shape)))))
                                (set! total-volume (+ total-volume (calculate-cylinder-volume (string->number(caddr shape)) (string->number(cadddr shape))))))
                            ((string=? (cadr shape) "sphere") 
                                (set! total-area (+ total-area (calculate-sphere-area (string->number(caddr shape)))))
                                (set! total-volume (+ total-volume (calculate-sphere-volume (string->number(caddr shape))))))
                            ((string=? (cadr shape) "torus") 
                                (set! total-area (+ total-area (calculate-torus-area (string->number(caddr shape)) (string->number(cadddr shape)))))
                                (set! total-volume (+ total-volume (calculate-torus-volume (string->number(caddr shape)) (string->number(cadddr shape)))))))))))
        shapes)
    ; Display avg surface area and volume by dividing total variables by total amount of qualifying shapes
    (newline)
    (display "avg(Surface Area)=") (display (exact->inexact(/ total-area num-satisfying))) (newline)
    (display "avg(Volume)=") (display (/ total-volume num-satisfying)) (newline)
    'done))