;; Emacs Lisp program to insert nodes and menus in a TeXinfo file.

(texinfo-mode)
(texinfo-insert-node-lines
  (save-excursion (beginning-of-buffer) (point))
  (save-excursion (end-of-buffer) (point))
  t
)
(texinfo-master-menu t)
;; The following is not needed because it is already done by the
;; (texinfo-master-menu t) command.
; (texinfo-every-node-update)
;; The following should not be needed because it should already done by the
;; (texinfo-master-menu t) command. Alas, `texinfo-master-menu' is buggy:
;; It forgets to create the `Customizing' menu...
(texinfo-all-menus-update)

