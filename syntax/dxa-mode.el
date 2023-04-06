;;; dxa-mode.el --- Major Mode for editing dxa Assembly Code -*- lexical-binding: t -*-

(defconst dxa-mode-syntax-table
  (with-syntax-table (copy-syntax-table)
    (modify-syntax-entry ?/ ". 124b")
    (modify-syntax-entry ?* ". 23")
    (modify-syntax-entry ?\n "> b")
    (modify-syntax-entry ?\" "\"")
    (modify-syntax-entry ?\' "\"")
    (syntax-table))
  "Syntax table for `dxa-mode'.")

(eval-and-compile
  (defconst dxa-instructions
    '("nop" "push" "pushf" "pusht" "push0"
      "push1" "pushn1" "pushu0" "pushu1" "pushf0"
      "pushf1" "pushfn1" "pop" "dup" "sdup" "jmp"
      "jt" "jf" "je" "jne" "jg" "jge" "jl" "jle" "rjmp"
      "rjt" "rjf" "rje" "rjne" "rjg" "rjge" "rjl" "rjle"
      "call" "load" "store" "ret" "swap" "sswap"
      "not" "and" "or" "xor" "rot"
      "add" "sub" "mul" "div" "neg" "eq" "neq"
      "lt" "lte" "gt" "gte" "inc" "read" "write"
      "dec" "scani" "scanu" "scanf" "scanc"
      "scanb" "scans" "print" "println" "prints"
      "printsln" "alloc" "realloc" "free" "readi"
      "readu" "readf" "readc" "readb" "writei"
      "writeu" "writef" "writec" "writeb" "i2u"
      "i2f" "i2c" "u2i" "u2f" "u2c"
      "u2b" "f2i" "f2u" "f2c" "c2i"
      "c2u" "c2f" "b2u" "n2b" "halt")))

(defconst dxa-highlights
  `(("%[[:word:]_]+" . font-lock-preprocessor-face)
    ("<\\(\\w\\|_\\|-\\|\\?\\)+>" . font-lock-constant-face)
    (,(regexp-opt dxa-instructions 'symbols) . font-lock-keyword-face)))

;;;###autoload
(define-derived-mode dxa-mode prog-mode "dxa"
  "Major Mode for editing dxa Assembly Code."
  (setq font-lock-defaults '(dxa-highlights))
  (set-syntax-table dxa-mode-syntax-table))

;;;###autoload
(add-to-list 'auto-mode-alist '("\\.dxa\\'" . dxa-mode))

(provide 'dxa-mode)

;;; dxa-mode.el ends here
