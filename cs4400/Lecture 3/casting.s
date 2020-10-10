f:
 subl	%esi, %edi
 movsbl	%dl, %edx
 movl	%edi, %eax
 imull	%edx, %eax
 ret
