f:
 movl	%edi, %eax
 addl	(%rcx), %eax
 movl	%eax, (%rcx)
 ret

