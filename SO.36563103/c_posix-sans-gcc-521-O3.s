	.text
Ltext0:
	.cstring
LC0:
	.ascii "Received SIGINT\12\0"
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDB1:
	.text
LHOTB1:
	.align 4,0x90
	.section __TEXT,__text_cold,regular,pure_instructions
Ltext_cold0:
	.text
_sighandler:
LFB21:
LM1:
LVL0:
LM2:
	movl	$16, %edx
LVL1:
	movl	$2, %edi
LVL2:
	leaq	LC0(%rip), %rsi
LVL3:
	jmp	_write
LVL4:
LFE21:
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDE1:
	.text
LHOTE1:
	.cstring
LC2:
	.ascii "(%d: %s)\12\0"
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDB3:
LHOTB3:
_err_syserr:
LFB14:
LM3:
LVL5:
	pushq	%r12
LCFI0:
	movq	%rdi, %r12
	pushq	%rbp
LCFI1:
	pushq	%rbx
LCFI2:
	subq	$208, %rsp
LCFI3:
	testb	%al, %al
	movq	%rsi, 40(%rsp)
	movq	%rdx, 48(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
	je	L5
	movaps	%xmm0, 80(%rsp)
	movaps	%xmm1, 96(%rsp)
	movaps	%xmm2, 112(%rsp)
	movaps	%xmm3, 128(%rsp)
	movaps	%xmm4, 144(%rsp)
	movaps	%xmm5, 160(%rsp)
	movaps	%xmm6, 176(%rsp)
	movaps	%xmm7, 192(%rsp)
L5:
LM4:
	call	___error
LVL6:
LM5:
	movq	___stderrp@GOTPCREL(%rip), %rbp
	leaq	8(%rsp), %rdx
	movq	%r12, %rsi
LM6:
	movl	(%rax), %ebx
LVL7:
LM7:
	leaq	240(%rsp), %rax
	movl	$8, 8(%rsp)
	movq	%rax, 16(%rsp)
	leaq	32(%rsp), %rax
	movl	$48, 12(%rsp)
LM8:
	movq	0(%rbp), %rdi
LM9:
	movq	%rax, 24(%rsp)
LM10:
	call	_vfprintf
LVL8:
LM11:
	testl	%ebx, %ebx
	je	L4
LM12:
	movl	%ebx, %edi
	call	_strerror
LVL9:
	movq	0(%rbp), %rdi
	movl	%ebx, %edx
	leaq	LC2(%rip), %rsi
	movq	%rax, %rcx
	xorl	%eax, %eax
	call	_fprintf
LVL10:
L4:
LM13:
	movl	$1, %edi
	call	_exit
LVL11:
LFE14:
LCOLDE3:
LHOTE3:
	.cstring
LC4:
	.ascii "%s:%d: \0"
LC5:
	.ascii " (%d: %s)\0"
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDB6:
	.text
LHOTB6:
	.align 4,0x90
_err_sysexit:
LFB13:
LM14:
LVL12:
	pushq	%r12
LCFI4:
	movq	%rdi, %r12
	pushq	%rbp
LCFI5:
	pushq	%rbx
LCFI6:
	subq	$208, %rsp
LCFI7:
	testb	%al, %al
	movq	%rsi, 40(%rsp)
	movq	%rdx, 48(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
	je	L14
	movaps	%xmm0, 80(%rsp)
	movaps	%xmm1, 96(%rsp)
	movaps	%xmm2, 112(%rsp)
	movaps	%xmm3, 128(%rsp)
	movaps	%xmm4, 144(%rsp)
	movaps	%xmm5, 160(%rsp)
	movaps	%xmm6, 176(%rsp)
	movaps	%xmm7, 192(%rsp)
L14:
LM15:
	leaq	240(%rsp), %rax
	movl	$8, 8(%rsp)
	movq	%rax, 16(%rsp)
	leaq	32(%rsp), %rax
	movl	$48, 12(%rsp)
	movq	%rax, 24(%rsp)
LVL13:
LBB19:
LBB20:
LM16:
	call	___error
LVL14:
	movl	(%rax), %ebp
LVL15:
LM17:
	call	_getpid
LVL16:
	movq	___stderrp@GOTPCREL(%rip), %rbx
	leaq	LC4(%rip), %rsi
	movq	_arg0(%rip), %rdx
	movl	%eax, %ecx
	xorl	%eax, %eax
	movq	(%rbx), %rdi
	call	_fprintf
LVL17:
LM18:
	movq	(%rbx), %rdi
	leaq	8(%rsp), %rdx
LVL18:
	movq	%r12, %rsi
	call	_vfprintf
LVL19:
LM19:
	testl	%ebp, %ebp
	je	L13
LM20:
	movl	%ebp, %edi
	call	_strerror
LVL20:
	movq	(%rbx), %rdi
	movl	%ebp, %edx
	leaq	LC5(%rip), %rsi
	movq	%rax, %rcx
	xorl	%eax, %eax
	call	_fprintf
LVL21:
L13:
LM21:
	movq	(%rbx), %rsi
	movl	$10, %edi
	call	_putc
LVL22:
LBE20:
LBE19:
LM22:
	movl	$1, %edi
	call	_exit
LVL23:
LFE13:
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDE6:
	.text
LHOTE6:
	.cstring
LC7:
	.ascii "ncmds >= 1\0"
LC8:
	.ascii "c_posix.c\0"
LC9:
	.ascii "Failed to create pipe\0"
LC10:
	.ascii "Failed to fork\0"
LC11:
	.ascii "Failed to exec %s\0"
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDB12:
	.text
LHOTB12:
	.align 4,0x90
_exec_nth_command:
LFB3:
LM23:
LVL24:
	pushq	%rbp
LCFI8:
	pushq	%rbx
LCFI9:
	movslq	%edi, %rbx
	subq	$24, %rsp
LCFI10:
LM24:
	testl	%ebx, %ebx
	jle	L29
LM25:
	cmpl	$1, %ebx
	movq	%rsi, %rbp
	je	L21
LBB24:
LM26:
	movq	%rsp, %rdi
LVL25:
	call	_pipe
LVL26:
	testl	%eax, %eax
	jne	L30
LM27:
	call	_fork
LVL27:
	testl	%eax, %eax
	js	L31
LM28:
	je	L32
LM29:
	movl	(%rsp), %edi
	xorl	%esi, %esi
	call	_dup2
LVL28:
LM30:
	movl	(%rsp), %edi
	call	_close
LVL29:
LM31:
	movl	4(%rsp), %edi
	call	_close
LVL30:
L21:
LBE24:
LM32:
	leaq	-8(%rbp,%rbx,8), %rbx
LVL31:
	movq	(%rbx), %rax
	movq	(%rax), %rdi
	movq	%rax, %rsi
	call	_execvp
LVL32:
LM33:
	movq	(%rbx), %rax
	leaq	LC11(%rip), %rdi
	movq	(%rax), %rsi
	xorl	%eax, %eax
	call	_err_sysexit
LVL33:
L30:
LBB27:
LM34:
	leaq	LC9(%rip), %rdi
	xorl	%eax, %eax
	call	_err_sysexit
LVL34:
L29:
LBE27:
LM35:
	leaq	LC7(%rip), %rcx
	movl	$49, %edx
	leaq	LC8(%rip), %rsi
LVL35:
	leaq	___func__.3142(%rip), %rdi
LVL36:
	call	___assert_rtn
LVL37:
L32:
LBB28:
LBB25:
LBB26:
LM36:
	movl	4(%rsp), %edi
	movl	$1, %esi
	call	_dup2
LVL38:
LM37:
	movl	(%rsp), %edi
	call	_close
LVL39:
LM38:
	movl	4(%rsp), %edi
	call	_close
LVL40:
LM39:
	leal	-1(%rbx), %edi
LVL41:
	movq	%rbp, %rsi
	call	_exec_nth_command
LVL42:
L31:
LBE26:
LBE25:
LM40:
	leaq	LC10(%rip), %rdi
	xorl	%eax, %eax
LVL43:
	call	_err_sysexit
LVL44:
LBE28:
LFE3:
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDE12:
	.text
LHOTE12:
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDB13:
	.text
LHOTB13:
	.align 4,0x90
_err_syswarn.constprop.6:
LFB23:
LM41:
LVL45:
	pushq	%rbp
LCFI11:
	pushq	%rbx
LCFI12:
	subq	$40, %rsp
LCFI13:
LM42:
	leaq	64(%rsp), %rax
	movq	%rax, 16(%rsp)
LVL46:
LBB31:
LBB32:
LM43:
	call	___error
LVL47:
	movl	(%rax), %ebp
LVL48:
LM44:
	call	_getpid
LVL49:
	movq	___stderrp@GOTPCREL(%rip), %rbx
	leaq	LC4(%rip), %rsi
	movq	_arg0(%rip), %rdx
	movl	%eax, %ecx
	xorl	%eax, %eax
	movq	(%rbx), %rdi
	call	_fprintf
LVL50:
LM45:
	movq	(%rbx), %rcx
	movl	$14, %edx
	movl	$1, %esi
	leaq	LC10(%rip), %rdi
	call	_fwrite
LVL51:
LM46:
	testl	%ebp, %ebp
	je	L34
LM47:
	movl	%ebp, %edi
	call	_strerror
LVL52:
	movq	(%rbx), %rdi
	movl	%ebp, %edx
	leaq	LC5(%rip), %rsi
	movq	%rax, %rcx
	xorl	%eax, %eax
	call	_fprintf
LVL53:
L34:
LM48:
	movq	(%rbx), %rsi
	movl	$10, %edi
	call	_putc
LVL54:
LBE32:
LBE31:
LM49:
	addq	$40, %rsp
LCFI14:
	popq	%rbx
LCFI15:
	popq	%rbp
LCFI16:
LVL55:
	ret
LFE23:
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDE13:
	.text
LHOTE13:
	.cstring
LC14:
	.ascii "(null)\0"
LC15:
	.ascii "printenv\0"
LC16:
	.ascii "sort\0"
LC17:
	.ascii "less\0"
LC18:
	.ascii "PATH\0"
LC19:
	.ascii "'%s' is not set.\12\0"
LC20:
	.ascii "'%s' is set to %s.\12\0"
LC21:
	.ascii ":\0"
LC22:
	.ascii "malloc failed!\0"
LC23:
	.ascii "\12\12\12\12%d terminated \12\12\12\12\12\0"
LC24:
	.ascii "exit\0"
LC25:
	.ascii "cd\0"
	.align 3
LC26:
	.ascii "Failed changing to homedirectory\12\0"
LC27:
	.ascii " \0"
LC28:
	.ascii "Failed changing directory\12\0"
LC29:
	.ascii "more\0"
LC30:
	.ascii "grep\0"
LC31:
	.ascii "-E\0"
LC32:
	.ascii "Failed creating pipe\0"
	.align 3
LC33:
	.ascii "dup2() failed on stdin for %s: \0"
	.align 3
LC34:
	.ascii "dup2() failed on stdout for %s: \0"
LC35:
	.ascii "%d: executing %s\12\0"
LC36:
	.ascii "failed to execute %s: \0"
LC37:
	.ascii "fork failed: \0"
LC38:
	.ascii "Failed creating pipe\12\0"
LC39:
	.ascii "Entering exec_arguments\0"
LC40:
	.ascii "%s: (%d)\0"
LC41:
	.ascii " {%s}\0"
LC42:
	.ascii "argv[argc] == 0\0"
LC43:
	.ascii "|\0"
	.align 3
LC44:
	.ascii "Syntax error: pipe before any command\0"
	.align 3
LC45:
	.ascii "Syntax error: two pipes with no command between\0"
	.align 3
LC46:
	.ascii "Syntax error: pipe with no command following\0"
LC47:
	.ascii "SOC\0"
LC48:
	.ascii "cmd [%d]\0"
LC49:
	.ascii "EOC\0"
LC50:
	.ascii "%d: child %d status 0x%.4X\12\0"
LC51:
	.ascii "Execution time %ld.%03ld ms\12\0"
LC52:
	.ascii "PAGER\0"
LC53:
	.ascii "miniShell>> \0"
LC54:
	.ascii "unixinfo\0"
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDB55:
	.section __TEXT,__text_startup,regular,pure_instructions
LHOTB55:
	.align 4
	.globl _main
_main:
LFB22:
LM50:
LVL56:
	pushq	%r15
LCFI17:
LM51:
	leaq	LC15(%rip), %rax
LM52:
	movl	$2, %edi
LVL57:
LM53:
	pushq	%r14
LCFI18:
	pushq	%r13
LCFI19:
	pushq	%r12
LCFI20:
	pushq	%rbp
LCFI21:
	pushq	%rbx
LCFI22:
	subq	$2392, %rsp
LCFI23:
LM54:
	movq	%rax, 128(%rsp)
LM55:
	leaq	LC16(%rip), %rax
	movq	%rax, 144(%rsp)
LM56:
	leaq	LC17(%rip), %rax
LM57:
	movq	%rsi, 16(%rsp)
LM58:
	leaq	224(%rsp), %rdx
LM59:
	movq	%rax, 160(%rsp)
LM60:
	leaq	208(%rsp), %rsi
LVL58:
LM61:
	leaq	_sighandler(%rip), %rax
LM62:
	movq	$0, 216(%rsp)
LM63:
	movq	$0, 136(%rsp)
LM64:
	movq	$0, 152(%rsp)
LM65:
	movq	$0, 168(%rsp)
LM66:
	movl	$0, 76(%rsp)
LVL59:
LM67:
	movq	%rax, 208(%rsp)
LM68:
	movl	$64, 220(%rsp)
LM69:
	call	_sigaction
LVL60:
LM70:
	leaq	LC18(%rip), %rdi
	call	_getenv
LVL61:
LM71:
	testq	%rax, %rax
LM72:
	movq	%rax, %rbx
LVL62:
LM73:
	je	L195
LM74:
	leaq	LC18(%rip), %rsi
	movq	%rax, %rdx
	xorl	%eax, %eax
LVL63:
	leaq	LC20(%rip), %rdi
	call	_printf
LVL64:
L41:
LBB77:
LBB78:
LM75:
	leaq	1360(%rsp), %r12
LBE78:
LBE77:
LM76:
	movq	%rbx, %rdi
	call	_strdup
LVL65:
LM77:
	leaq	LC21(%rip), %rsi
	movq	%rax, %rdi
LM78:
	movq	%rax, %rbp
LVL66:
LM79:
	call	_strtok
LVL67:
LM80:
	testq	%rax, %rax
LM81:
	movq	%rax, %rbx
LVL68:
LM82:
	jne	L154
	jmp	L50
LVL69:
	.align 4
L44:
LM83:
	leaq	LC22(%rip), %rdi
	call	_puts
LVL70:
L109:
LM84:
	leaq	LC21(%rip), %rsi
	xorl	%edi, %edi
	call	_strtok
LVL71:
LM85:
	testq	%rax, %rax
LM86:
	movq	%rax, %rbx
LVL72:
LM87:
	je	L50
LVL73:
L154:
LM88:
	movq	%rbx, %rdi
	call	_strlen
LVL74:
	leaq	6(%rax), %rdi
	call	_malloc
LVL75:
	testq	%rax, %rax
	movq	%rax, %r13
LVL76:
	je	L44
LM89:
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_strcpy
LVL77:
LM90:
	movq	%r13, %rdx
L45:
	movl	(%rdx), %ecx
	addq	$4, %rdx
	leal	-16843009(%rcx), %eax
	notl	%ecx
	andl	%ecx, %eax
	andl	$-2139062144, %eax
	je	L45
	movl	%eax, %ecx
LBB81:
LBB79:
LM91:
	movq	%r12, %rsi
	movq	%r13, %rdi
LBE79:
LBE81:
LM92:
	shrl	$16, %ecx
	testl	$32896, %eax
	cmove	%ecx, %eax
	leaq	2(%rdx), %rcx
	cmove	%rcx, %rdx
	addb	%al, %al
	movl	$115, %eax
	sbbq	$3, %rdx
	movl	$1936026671, (%rdx)
	movw	%ax, 4(%rdx)
LVL78:
LBB82:
LBB80:
LM93:
	call	_stat$INODE64
LVL79:
LBE80:
LBE82:
LM94:
	testl	%eax, %eax
	jne	L196
LVL80:
LM95:
	movq	%r13, %rdi
	call	_free
LVL81:
LM96:
	movl	$0, 32(%rsp)
LVL82:
L43:
	leaq	88(%rsp), %r15
LM97:
	movq	%rbp, %rdi
	call	_free
LVL83:
LM98:
	leaq	1360(%rsp), %rax
LM99:
	movl	$0, 36(%rsp)
LM100:
	movq	%rax, 8(%rsp)
	leaq	304(%rsp), %rax
	movq	%rax, 40(%rsp)
LM101:
	leaq	76(%rsp), %rax
	leaq	84(%rsp), %r12
	movq	%rax, 48(%rsp)
	leaq	336(%rsp), %rbx
LVL84:
	movq	%r15, (%rsp)
LVL85:
L57:
	movl	$20, 84(%rsp)
LVL86:
L120:
LBB83:
LBB84:
LBB85:
LM102:
	movl	$1, %edx
	movq	%r12, %rsi
	movl	$-1, %edi
	call	_waitpid
LVL87:
LM103:
	testl	%eax, %eax
	jle	L51
LM104:
	cmpl	_foreground(%rip), %eax
	je	L120
LM105:
	movl	84(%rsp), %edx
	andl	$127, %edx
	cmpl	$127, %edx
	je	L120
LM106:
	leaq	LC23(%rip), %rdi
	movl	%eax, %esi
	xorl	%eax, %eax
LVL88:
	call	_printf
LVL89:
	jmp	L120
LVL90:
L196:
LBE85:
LBE84:
LBE83:
LM107:
	movq	%r13, %rdi
	call	_free
LVL91:
	jmp	L109
LVL92:
	.align 4
L51:
LM108:
	leaq	LC53(%rip), %rdi
	xorl	%eax, %eax
LVL93:
	call	_printf
LVL94:
LM109:
	xorl	%esi, %esi
	movl	$1024, %edx
	movq	%rbx, %rdi
	call	_memset
LVL95:
LM110:
	movq	___stdinp@GOTPCREL(%rip), %rax
	movl	$1024, %esi
	movq	%rbx, %rdi
	movq	(%rax), %rdx
	call	_fgets
LVL96:
	testq	%rax, %rax
	je	L142
	movl	$20, 88(%rsp)
LVL97:
L122:
LBB86:
LBB87:
LBB88:
LM111:
	movq	(%rsp), %rsi
	movl	$1, %edx
	movl	$-1, %edi
	call	_waitpid
LVL98:
LM112:
	testl	%eax, %eax
	jle	L53
LM113:
	cmpl	_foreground(%rip), %eax
	je	L122
LM114:
	movl	88(%rsp), %edx
	andl	$127, %edx
	cmpl	$127, %edx
	je	L122
LM115:
	leaq	LC23(%rip), %rdi
	movl	%eax, %esi
	xorl	%eax, %eax
LVL99:
	call	_printf
LVL100:
	jmp	L122
LVL101:
	.align 4
L53:
LBE88:
LBE87:
LBE86:
LM116:
	movq	8(%rsp), %r14
	movl	$1024, %edx
	movq	%rbx, %rsi
	movq	%r14, %rdi
	call	_strncpy
LVL102:
LBB89:
LBB90:
LM117:
	movq	%r14, %rcx
LM118:
	movq	%r14, %rdx
	jmp	L121
LVL103:
	.align 4
L56:
LM119:
	addq	$1, %rcx
LVL104:
LM120:
	cmpb	$32, %al
LM121:
	movb	%al, (%rdx)
LM122:
	setne	%al
	movzbl	%al, %eax
	addq	%rax, %rdx
LVL105:
L121:
LM123:
	movzbl	(%rcx), %eax
	testb	%al, %al
	jne	L56
LM124:
	movb	$0, (%rdx)
LVL106:
LBE90:
LBE89:
LBB91:
LBB92:
LM125:
	cmpb	$10, 1360(%rsp)
LBE92:
LBE91:
LM126:
	movq	%rbx, %rdx
LVL107:
LBB94:
LBB93:
LM127:
	je	L57
LVL108:
L110:
LBE93:
LBE94:
LM128:
	movl	(%rdx), %ecx
	addq	$4, %rdx
	leal	-16843009(%rcx), %eax
	notl	%ecx
	andl	%ecx, %eax
	andl	$-2139062144, %eax
	je	L110
	movl	%eax, %ecx
	shrl	$16, %ecx
	testl	$32896, %eax
	cmove	%ecx, %eax
	leaq	2(%rdx), %rcx
	cmove	%rcx, %rdx
	addb	%al, %al
	sbbq	$3, %rdx
	subq	%rbx, %rdx
LVL109:
LM129:
	subq	$1, %rdx
LVL110:
	cmpb	$10, 336(%rsp,%rdx)
	jne	L113
LM130:
	movb	$0, 336(%rsp,%rdx)
L113:
LM131:
	leaq	LC24(%rip), %rdi
	movl	$5, %ecx
	movq	%rbx, %rsi
	repz cmpsb
	je	L142
LVL111:
LBB95:
LBB96:
LM132:
	leaq	LC25(%rip), %rdi
	movl	$2, %ecx
	movq	%rbx, %rsi
	repz cmpsb
	je	L197
LVL112:
LBE96:
LBE95:
LBB97:
LBB98:
	leaq	LC54(%rip), %rdi
	movl	$8, %ecx
	movq	%rbx, %rsi
	repz cmpsb
	je	L123
	movq	%rbx, %rax
	xorl	%r15d, %r15d
	movl	$1, %edx
LVL113:
	leaq	80(%rbx), %rcx
	.align 4
L75:
	cmpb	$38, (%rax)
	cmove	%edx, %r15d
LVL114:
	addq	$1, %rax
LVL115:
LBE98:
LBE97:
LM133:
	cmpq	%rax, %rcx
	jne	L75
LM134:
	cmpl	$1, %r15d
	je	L198
LM135:
	leaq	176(%rsp), %rdi
	xorl	%esi, %esi
	call	_gettimeofday
LVL116:
LM136:
	cmpl	$1, _isSignal(%rip)
	je	L199
L79:
LM137:
	movl	36(%rsp), %eax
	movl	%eax, _foreground(%rip)
L78:
LVL117:
LBB100:
LBB101:
LM138:
	movq	16(%rsp), %rax
LBE101:
LBE100:
LM139:
	leaq	LC27(%rip), %rsi
	movq	%rbx, %rdi
LBB103:
LBB102:
LM140:
	movq	(%rax), %rax
	movq	%rax, _arg0(%rip)
LVL118:
LBE102:
LBE103:
LM141:
	call	_strtok
LVL119:
LM142:
	movq	$0, 240(%rsp)
LM143:
	testq	%rax, %rax
	je	L126
	leaq	240(%rsp), %r13
	movl	$1, %ebp
	movq	%r13, %r14
LVL120:
L81:
LM144:
	movq	%rax, 8(%r14)
LM145:
	xorl	%edi, %edi
LM146:
	addl	$1, %ebp
LVL121:
	addq	$8, %r14
LM147:
	leaq	LC27(%rip), %rsi
	call	_strtok
LVL122:
LM148:
	testq	%rax, %rax
	jne	L81
LVL123:
L80:
LM149:
	movslq	%ebp, %rax
LVL124:
LBB104:
LBB105:
LBB106:
LBB107:
LM150:
	movl	%ebp, %edx
	xorl	%r14d, %r14d
LBE107:
LBE106:
LBE105:
LBE104:
LM151:
	movq	%rax, 24(%rsp)
LBB143:
LBB136:
LBB112:
LBB109:
LM152:
	leaq	LC39(%rip), %rsi
LBE109:
LBE112:
LBE136:
LBE143:
LM153:
	movq	$0, 240(%rsp,%rax,8)
LVL125:
LBB144:
LBB137:
LBB113:
LBB110:
LM154:
	leaq	LC40(%rip), %rdi
	xorl	%eax, %eax
	call	_printf
LVL126:
	.align 4
L83:
LBB108:
LM155:
	movq	0(%r13,%r14,8), %rsi
	leaq	LC14(%rip), %rax
	leaq	LC41(%rip), %rdi
	testq	%rsi, %rsi
	cmove	%rax, %rsi
	xorl	%eax, %eax
	addq	$1, %r14
LVL127:
	call	_printf
LVL128:
LM156:
	cmpl	%r14d, %ebp
	jg	L83
LBE108:
LM157:
	movl	$10, %edi
	call	_putchar
LVL129:
LM158:
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	call	_fflush
LVL130:
LM159:
	movq	24(%rsp), %r13
LVL131:
	salq	$3, %r13
	cmpq	$0, 240(%rsp,%r13)
	jne	L200
LBE110:
LBE113:
LM160:
	movl	%ebp, %edi
	sarl	%edi
	movslq	%edi, %rdi
	salq	$3, %rdi
	call	_malloc
LVL132:
LM161:
	leaq	8(%r13), %rdi
LM162:
	movq	%rax, %r14
LVL133:
LM163:
	call	_malloc
LVL134:
LBB114:
LM164:
	cmpl	$1, %ebp
LBE114:
LM165:
	movq	%rax, %r13
LVL135:
LM166:
	movq	%rax, (%r14)
LVL136:
LBB121:
LM167:
	je	L127
LBB115:
LM168:
	movq	248(%rsp), %rdx
LVL137:
LM169:
	leaq	LC43(%rip), %rax
LVL138:
	movl	$2, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	repz cmpsb
LVL139:
	je	L86
LVL140:
LBE115:
LM170:
	cmpl	$2, %ebp
LBB116:
LM171:
	movq	%rdx, 0(%r13)
LVL141:
LBE116:
LM172:
	je	L128
LBB117:
LM173:
	movq	256(%rsp), %rdx
LVL142:
LM174:
	movl	$2, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	repz cmpsb
LVL143:
	jne	L88
LVL144:
LM175:
	leaq	16(%r13), %rdx
LM176:
	movq	$0, 8(%r13)
LVL145:
LM177:
	movq	%rdx, 8(%r14)
	movl	$2, 24(%rsp)
LVL146:
L89:
LBE117:
LM178:
	cmpl	$4, %ebp
	jne	L129
LBB118:
LM179:
	movq	264(%rsp), %rdx
LVL147:
LM180:
	movl	$2, %ecx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	repz cmpsb
LVL148:
	jne	L201
LM181:
	cmpq	$0, 8(%r13)
	je	L202
LVL149:
LM182:
	movl	24(%rsp), %esi
	leaq	24(%r13), %rdx
LM183:
	movq	$0, 16(%r13)
LVL150:
LM184:
	movslq	%esi, %rax
	movq	%rdx, (%r14,%rax,8)
	movl	%esi, %eax
	addl	$1, %eax
LVL151:
	movl	%eax, 24(%rsp)
	jmp	L118
LVL152:
	.align 4
L142:
LBE118:
LBE121:
LBE137:
LBE144:
LM185:
	addq	$2392, %rsp
LCFI24:
	xorl	%eax, %eax
	popq	%rbx
LCFI25:
	popq	%rbp
LCFI26:
	popq	%r12
LCFI27:
LVL153:
	popq	%r13
LCFI28:
	popq	%r14
LCFI29:
	popq	%r15
LCFI30:
	ret
LVL154:
	.align 4
L50:
LCFI31:
LM186:
	movl	$1, 32(%rsp)
	jmp	L43
LVL155:
L197:
LM187:
	movl	$32, %esi
	movq	%rbx, %rdi
	call	_strchr
LVL156:
	testq	%rax, %rax
	je	L203
LM188:
	leaq	LC27(%rip), %rsi
	movq	%rbx, %rdi
	call	_strtok
LVL157:
LM189:
	leaq	LC27(%rip), %rsi
	xorl	%edi, %edi
	call	_strtok
LVL158:
LM190:
	movq	%rax, %rdi
	call	_chdir
LVL159:
	cmpl	$-1, %eax
	je	L204
LVL160:
L63:
LBB145:
LBB99:
LM191:
	leaq	LC54(%rip), %rdi
	movl	$8, %ecx
	movq	%rbx, %rsi
	repz cmpsb
	jne	L106
LVL161:
L123:
LBE99:
LBE145:
LM192:
	leaq	LC52(%rip), %rdi
	call	_getenv
LVL162:
LM193:
	testq	%rax, %rax
	je	L205
LM194:
	movq	%rax, 160(%rsp)
LVL163:
L65:
LM195:
	movl	$1, %edi
LBB146:
LBB147:
LM196:
	xorl	%ebp, %ebp
LM197:
	xorl	%ebx, %ebx
LBE147:
LBE146:
LM198:
	call	_malloc
LVL164:
LM199:
	leaq	LC30(%rip), %rsi
LM200:
	movq	$0, 296(%rsp)
LM201:
	movb	$0, (%rax)
LM202:
	leaq	160(%rsp), %r13
LM203:
	movq	%rax, 288(%rsp)
LM204:
	leaq	128(%rsp), %rax
LVL165:
	movq	%rax, 304(%rsp)
LM205:
	leaq	272(%rsp), %rax
LM206:
	movq	%rsi, 272(%rsp)
LM207:
	leaq	LC31(%rip), %rsi
LM208:
	movq	%rax, 312(%rsp)
LM209:
	leaq	144(%rsp), %rax
LM210:
	movq	%rsi, 280(%rsp)
	leaq	112(%rsp), %r14
LM211:
	movq	%rax, 320(%rsp)
LM212:
	movq	%r13, 328(%rsp)
LVL166:
L73:
LBB165:
LBB162:
LM213:
	movq	%r14, %rdi
	call	_pipe
LVL167:
	addl	$1, %eax
	je	L206
LM214:
	movl	116(%rsp), %r12d
LVL168:
LBB148:
LBB149:
LM215:
	call	_fork
LVL169:
	testl	%eax, %eax
	jne	L67
LBE149:
LBE148:
LM216:
	movslq	%ebx, %rbx
LVL170:
LBB156:
LBB150:
LM217:
	testl	%ebp, %ebp
LBE150:
LBE156:
LM218:
	leaq	304(%rsp,%rbx,8), %rbx
LVL171:
LBB157:
LBB151:
LM219:
	jne	L207
LVL172:
L68:
LM220:
	cmpl	$1, %r12d
	je	L70
LM221:
	movl	$1, %esi
	movl	%r12d, %edi
	call	_dup2
LVL173:
	testl	%eax, %eax
	js	L208
LM222:
	movl	%r12d, %edi
	call	_close
LVL174:
L70:
LM223:
	movq	(%rbx), %rbx
	movq	(%rbx), %rbp
LVL175:
	call	_getpid
LVL176:
	leaq	LC35(%rip), %rsi
	movl	%eax, %edx
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	%rbp, %rcx
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	_fprintf
LVL177:
LM224:
	movq	(%rbx), %rdi
	movq	%rbx, %rsi
	call	_execvp
LVL178:
LM225:
	movq	(%rbx), %rsi
	leaq	LC36(%rip), %rdi
	xorl	%eax, %eax
	call	_err_syserr
LVL179:
L103:
LBE151:
LBE157:
LBE162:
LBE165:
LM226:
	testl	%r15d, %r15d
	je	L104
LVL180:
L105:
LM227:
	movl	96(%rsp), %edi
	call	_close
LVL181:
LM228:
	movl	100(%rsp), %edi
	call	_close
LVL182:
L106:
LM229:
	movl	$1024, %edx
	xorl	%esi, %esi
	movq	%rbx, %rdi
	call	_memset
LVL183:
	jmp	L57
LVL184:
L86:
LBB166:
LBB138:
LBB122:
LBB119:
LM230:
	leaq	LC44(%rip), %rdi
	xorl	%eax, %eax
	call	_err_sysexit
LVL185:
L88:
LM231:
	movq	%rdx, 8(%r13)
	movl	$1, 24(%rsp)
	jmp	L89
LVL186:
L201:
	movq	%rdx, 16(%r13)
LVL187:
L118:
LM232:
	movl	$3, %eax
LVL188:
L85:
LBE119:
LBE122:
LM233:
	cmpq	$0, -8(%r13,%rax,8)
	je	L209
LM234:
	movq	$0, 0(%r13,%rax,8)
LVL189:
LBB123:
LBB124:
LM235:
	leaq	LC47(%rip), %rdi
	xorl	%ebp, %ebp
LVL190:
	call	_puts
LVL191:
	movq	%rbx, 56(%rsp)
LVL192:
L95:
LBB125:
LBB126:
LM236:
	leaq	LC48(%rip), %rdi
	movl	%ebp, %esi
	xorl	%eax, %eax
	call	_printf
LVL193:
LM237:
	movq	(%r14,%rbp,8), %rbx
LVL194:
LM238:
	movq	(%rbx), %rsi
	testq	%rsi, %rsi
	je	L98
	.align 4
L153:
LM239:
	leaq	LC41(%rip), %rdi
	addq	$8, %rbx
LVL195:
	xorl	%eax, %eax
	call	_printf
LVL196:
LM240:
	movq	(%rbx), %rsi
	testq	%rsi, %rsi
	jne	L153
L98:
LM241:
	movl	$10, %edi
	addq	$1, %rbp
LVL197:
	call	_putchar
LVL198:
LBE126:
LM242:
	cmpl	%ebp, 24(%rsp)
	jg	L95
LBE125:
LM243:
	leaq	LC49(%rip), %rdi
	movq	56(%rsp), %rbx
LVL199:
	call	_puts
LVL200:
LM244:
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	call	_fflush
LVL201:
LBE124:
LBE123:
LBB127:
LBB128:
LM245:
	call	_fork
LVL202:
	testl	%eax, %eax
	js	L210
LM246:
	je	L211
LVL203:
L100:
LBE128:
LBE127:
LM247:
	movq	%r14, %rdi
	call	_free
LVL204:
LM248:
	movq	%r13, %rdi
	call	_free
LVL205:
LBE138:
LBE166:
LBB167:
LBB168:
LM249:
	call	_getpid
LVL206:
	movq	40(%rsp), %r13
LVL207:
	movl	%eax, %ebp
LVL208:
	jmp	L101
LVL209:
L102:
LM250:
	movl	%eax, %ecx
	movq	___stderrp@GOTPCREL(%rip), %rax
LVL210:
	movl	%ebp, %edx
	movl	304(%rsp), %r8d
	leaq	LC50(%rip), %rsi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	_fprintf
LVL211:
L101:
LM251:
	xorl	%edx, %edx
	xorl	%edi, %edi
	movq	%r13, %rsi
	call	_waitpid
LVL212:
	cmpl	$-1, %eax
	jne	L102
LBE168:
LBE167:
LM252:
	cmpl	$0, 36(%rsp)
	jne	L103
LM253:
	subl	$1, %r15d
LVL213:
	je	L212
L104:
LM254:
	movq	48(%rsp), %rsi
	xorl	%edx, %edx
	movl	_foreground(%rip), %edi
	call	_waitpid
LVL214:
LM255:
	leaq	192(%rsp), %rdi
	xorl	%esi, %esi
	call	_gettimeofday
LVL215:
LM256:
	movq	192(%rsp), %rax
LM257:
	movl	$1000, %ecx
LM258:
	subq	176(%rsp), %rax
LM259:
	leaq	LC51(%rip), %rdi
LM260:
	imulq	$1000000, %rax, %rdx
	movslq	200(%rsp), %rax
	addq	%rdx, %rax
	movslq	184(%rsp), %rdx
	subq	%rdx, %rax
LVL216:
LM261:
	cqto
	idivq	%rcx
LVL217:
	movq	%rax, %rsi
	xorl	%eax, %eax
	call	_printf
LVL218:
LM262:
	cmpl	$1, _isSignal(%rip)
	jne	L106
LBB169:
LM263:
	leaq	80(%rsp), %rsi
	xorl	%edx, %edx
	movl	$2, %edi
	call	_sigprocmask
LVL219:
	leaq	92(%rsp), %rbp
LVL220:
	movl	$20, 92(%rsp)
LVL221:
L125:
LBB170:
LBB171:
LBB172:
LM264:
	orl	$-1, %edi
	movl	$1, %edx
	movq	%rbp, %rsi
	call	_waitpid
LVL222:
LM265:
	testl	%eax, %eax
	jle	L106
LM266:
	cmpl	_foreground(%rip), %eax
	je	L125
LM267:
	movl	92(%rsp), %edx
	andl	$127, %edx
	cmpl	$127, %edx
	je	L125
LM268:
	leaq	LC23(%rip), %rdi
	movl	%eax, %esi
	xorl	%eax, %eax
LVL223:
	call	_printf
LVL224:
	jmp	L125
LVL225:
L126:
	leaq	240(%rsp), %r13
LBE172:
LBE171:
LBE170:
LBE169:
LM269:
	movl	$1, %ebp
	jmp	L80
LVL226:
L195:
LM270:
	leaq	LC18(%rip), %rsi
	xorl	%eax, %eax
LVL227:
	leaq	LC19(%rip), %rdi
	call	_printf
LVL228:
	jmp	L41
LVL229:
L203:
LM271:
	call	_getuid
LVL230:
	movl	%eax, %edi
	call	_getpwuid
LVL231:
LM272:
	movq	48(%rax), %rdi
	call	_chdir
LVL232:
	addl	$1, %eax
	jne	L63
LM273:
	leaq	LC26(%rip), %rdi
	call	_perror
LVL233:
	jmp	L63
LVL234:
L198:
LM274:
	leaq	96(%rsp), %rdi
	call	_pipe
LVL235:
	addl	$1, %eax
	je	L213
L77:
LM275:
	call	_fork
LVL236:
	movl	%eax, 36(%rsp)
LVL237:
	jmp	L78
LVL238:
L204:
LM276:
	leaq	LC28(%rip), %rdi
	call	_perror
LVL239:
	jmp	L63
LVL240:
L200:
LBB173:
LBB139:
LBB131:
LBB111:
LM277:
	leaq	LC42(%rip), %rcx
	movl	$120, %edx
	leaq	LC8(%rip), %rsi
	leaq	___func__.3171(%rip), %rdi
	call	___assert_rtn
LVL241:
L199:
LBE111:
LBE131:
LBE139:
LBE173:
LM278:
	leaq	80(%rsp), %rsi
	xorl	%edx, %edx
	movl	$1, %edi
LM279:
	movl	$524288, 80(%rsp)
LM280:
	call	_sigprocmask
LVL242:
	jmp	L79
LVL243:
L127:
LBB174:
LBB140:
LM281:
	movl	$1, 24(%rsp)
LM282:
	xorl	%eax, %eax
LVL244:
	jmp	L85
LVL245:
L213:
LBE140:
LBE174:
LM283:
	leaq	LC38(%rip), %rdi
	call	_perror
LVL246:
	jmp	L77
LVL247:
L210:
LBB175:
LBB141:
LBB132:
LBB129:
LM284:
	leaq	LC10(%rip), %rdi
	xorl	%eax, %eax
LVL248:
	call	_err_syswarn.constprop.6
LVL249:
	jmp	L100
LVL250:
L128:
LBE129:
LBE132:
LBB133:
LM285:
	movl	$1, %eax
	movl	$1, 24(%rsp)
	jmp	L85
LVL251:
L129:
	movl	$2, %eax
	jmp	L85
LVL252:
L209:
LBE133:
LM286:
	leaq	LC46(%rip), %rdi
	xorl	%eax, %eax
	call	_err_sysexit
LVL253:
L202:
LBB134:
LBB120:
LM287:
	leaq	LC45(%rip), %rdi
	xorl	%eax, %eax
	call	_err_sysexit
LVL254:
L212:
LBE120:
LBE134:
LBE141:
LBE175:
LM288:
	movl	96(%rsp), %edi
	xorl	%esi, %esi
	call	_dup2
LVL255:
LM289:
	movl	96(%rsp), %edi
	call	_close
LVL256:
LM290:
	movl	100(%rsp), %edi
	call	_close
LVL257:
	jmp	L105
LVL258:
L211:
LBB176:
LBB142:
LBB135:
LBB130:
LM291:
	movl	24(%rsp), %edi
	movq	%r14, %rsi
	call	_exec_nth_command
LVL259:
L207:
LBE130:
LBE135:
LBE142:
LBE176:
LBB177:
LBB163:
LBB158:
LBB152:
LM292:
	xorl	%esi, %esi
	movl	%ebp, %edi
	call	_dup2
LVL260:
	testl	%eax, %eax
	js	L214
LM293:
	movl	%ebp, %edi
	call	_close
LVL261:
	jmp	L68
LVL262:
L67:
LM294:
	js	L215
LBE152:
LBE158:
LM295:
	movl	116(%rsp), %edi
LM296:
	addl	$1, %ebx
LVL263:
LM297:
	call	_close
LVL264:
LM298:
	cmpl	$3, %ebx
LM299:
	movl	112(%rsp), %ebp
LVL265:
LM300:
	jne	L73
LM301:
	xorl	%esi, %esi
	movl	%ebp, %edi
	call	_dup2
LVL266:
	testl	%eax, %eax
	js	L216
LM302:
	movq	160(%rsp), %rbx
LVL267:
	call	_getpid
LVL268:
	leaq	LC35(%rip), %rsi
	movl	%eax, %edx
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	%rbx, %rcx
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	_fprintf
LVL269:
LM303:
	movq	160(%rsp), %rdi
	movq	%r13, %rsi
	call	_execvp
LVL270:
LM304:
	movq	160(%rsp), %rsi
	leaq	LC36(%rip), %rdi
	xorl	%eax, %eax
	call	_err_syserr
LVL271:
L205:
LBE163:
LBE177:
LM305:
	cmpl	$0, 32(%rsp)
	leaq	LC17(%rip), %rdx
	leaq	LC29(%rip), %rax
LVL272:
	cmove	%rdx, %rax
	movq	%rax, 160(%rsp)
	jmp	L65
LVL273:
L208:
LBB178:
LBB164:
LBB159:
LBB153:
LM306:
	movq	(%rbx), %rax
	leaq	LC34(%rip), %rdi
	movq	(%rax), %rsi
	xorl	%eax, %eax
	call	_err_syserr
LVL274:
L206:
LBE153:
LBE159:
LM307:
	leaq	LC32(%rip), %rdi
	xorl	%eax, %eax
	call	_err_syserr
LVL275:
L214:
LBB160:
LBB154:
LM308:
	movq	(%rbx), %rax
	leaq	LC33(%rip), %rdi
	movq	(%rax), %rsi
	xorl	%eax, %eax
	call	_err_syserr
LVL276:
L216:
LBE154:
LBE160:
LM309:
	movq	160(%rsp), %rsi
	leaq	LC33(%rip), %rdi
	xorl	%eax, %eax
	call	_err_syserr
LVL277:
L215:
LBB161:
LBB155:
LM310:
	leaq	LC37(%rip), %rdi
	xorl	%eax, %eax
LVL278:
	call	_err_syserr
LVL279:
LBE155:
LBE161:
LBE164:
LBE178:
LFE22:
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDE55:
	.section __TEXT,__text_startup,regular,pure_instructions
LHOTE55:
	.const
	.align 4
___func__.3142:
	.ascii "exec_nth_command\0"
	.align 3
___func__.3171:
	.ascii "dump_argv\0"
	.globl _foreground
	.data
	.align 2
_foreground:
	.long	-1
	.cstring
LC56:
	.ascii "<undefined>\0"
	.data
	.align 3
_arg0:
	.quad	LC56
	.globl _isSignal
	.zerofill __DATA,__pu_bss2,_isSignal,4,2
	.section __DWARF,__debug_frame,regular,debug
Lsection__debug_frame:
Lframe0:
	.set L$set$0,LECIE0-LSCIE0
	.long L$set$0
LSCIE0:
	.long	0xffffffff
	.byte	0x1
	.ascii "\0"
	.byte	0x1
	.byte	0x78
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.byte	0x90
	.byte	0x1
	.align 3
LECIE0:
LSFDE0:
	.set L$set$1,LEFDE0-LASFDE0
	.long L$set$1
LASFDE0:
	.set L$set$2,Lframe0-Lsection__debug_frame
	.long L$set$2
	.quad	LFB21
	.set L$set$3,LFE21-LFB21
	.quad L$set$3
	.align 3
LEFDE0:
LSFDE2:
	.set L$set$4,LEFDE2-LASFDE2
	.long L$set$4
LASFDE2:
	.set L$set$5,Lframe0-Lsection__debug_frame
	.long L$set$5
	.quad	LFB14
	.set L$set$6,LFE14-LFB14
	.quad L$set$6
	.byte	0x4
	.set L$set$7,LCFI0-LFB14
	.long L$set$7
	.byte	0xe
	.byte	0x10
	.byte	0x8c
	.byte	0x2
	.byte	0x4
	.set L$set$8,LCFI1-LCFI0
	.long L$set$8
	.byte	0xe
	.byte	0x18
	.byte	0x86
	.byte	0x3
	.byte	0x4
	.set L$set$9,LCFI2-LCFI1
	.long L$set$9
	.byte	0xe
	.byte	0x20
	.byte	0x83
	.byte	0x4
	.byte	0x4
	.set L$set$10,LCFI3-LCFI2
	.long L$set$10
	.byte	0xe
	.byte	0xf0,0x1
	.align 3
LEFDE2:
LSFDE4:
	.set L$set$11,LEFDE4-LASFDE4
	.long L$set$11
LASFDE4:
	.set L$set$12,Lframe0-Lsection__debug_frame
	.long L$set$12
	.quad	LFB13
	.set L$set$13,LFE13-LFB13
	.quad L$set$13
	.byte	0x4
	.set L$set$14,LCFI4-LFB13
	.long L$set$14
	.byte	0xe
	.byte	0x10
	.byte	0x8c
	.byte	0x2
	.byte	0x4
	.set L$set$15,LCFI5-LCFI4
	.long L$set$15
	.byte	0xe
	.byte	0x18
	.byte	0x86
	.byte	0x3
	.byte	0x4
	.set L$set$16,LCFI6-LCFI5
	.long L$set$16
	.byte	0xe
	.byte	0x20
	.byte	0x83
	.byte	0x4
	.byte	0x4
	.set L$set$17,LCFI7-LCFI6
	.long L$set$17
	.byte	0xe
	.byte	0xf0,0x1
	.align 3
LEFDE4:
LSFDE6:
	.set L$set$18,LEFDE6-LASFDE6
	.long L$set$18
LASFDE6:
	.set L$set$19,Lframe0-Lsection__debug_frame
	.long L$set$19
	.quad	LFB3
	.set L$set$20,LFE3-LFB3
	.quad L$set$20
	.byte	0x4
	.set L$set$21,LCFI8-LFB3
	.long L$set$21
	.byte	0xe
	.byte	0x10
	.byte	0x86
	.byte	0x2
	.byte	0x4
	.set L$set$22,LCFI9-LCFI8
	.long L$set$22
	.byte	0xe
	.byte	0x18
	.byte	0x83
	.byte	0x3
	.byte	0x4
	.set L$set$23,LCFI10-LCFI9
	.long L$set$23
	.byte	0xe
	.byte	0x30
	.align 3
LEFDE6:
LSFDE8:
	.set L$set$24,LEFDE8-LASFDE8
	.long L$set$24
LASFDE8:
	.set L$set$25,Lframe0-Lsection__debug_frame
	.long L$set$25
	.quad	LFB23
	.set L$set$26,LFE23-LFB23
	.quad L$set$26
	.byte	0x4
	.set L$set$27,LCFI11-LFB23
	.long L$set$27
	.byte	0xe
	.byte	0x10
	.byte	0x86
	.byte	0x2
	.byte	0x4
	.set L$set$28,LCFI12-LCFI11
	.long L$set$28
	.byte	0xe
	.byte	0x18
	.byte	0x83
	.byte	0x3
	.byte	0x4
	.set L$set$29,LCFI13-LCFI12
	.long L$set$29
	.byte	0xe
	.byte	0x40
	.byte	0x4
	.set L$set$30,LCFI14-LCFI13
	.long L$set$30
	.byte	0xe
	.byte	0x18
	.byte	0x4
	.set L$set$31,LCFI15-LCFI14
	.long L$set$31
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$32,LCFI16-LCFI15
	.long L$set$32
	.byte	0xe
	.byte	0x8
	.align 3
LEFDE8:
LSFDE10:
	.set L$set$33,LEFDE10-LASFDE10
	.long L$set$33
LASFDE10:
	.set L$set$34,Lframe0-Lsection__debug_frame
	.long L$set$34
	.quad	LFB22
	.set L$set$35,LFE22-LFB22
	.quad L$set$35
	.byte	0x4
	.set L$set$36,LCFI17-LFB22
	.long L$set$36
	.byte	0xe
	.byte	0x10
	.byte	0x8f
	.byte	0x2
	.byte	0x4
	.set L$set$37,LCFI18-LCFI17
	.long L$set$37
	.byte	0xe
	.byte	0x18
	.byte	0x8e
	.byte	0x3
	.byte	0x4
	.set L$set$38,LCFI19-LCFI18
	.long L$set$38
	.byte	0xe
	.byte	0x20
	.byte	0x8d
	.byte	0x4
	.byte	0x4
	.set L$set$39,LCFI20-LCFI19
	.long L$set$39
	.byte	0xe
	.byte	0x28
	.byte	0x8c
	.byte	0x5
	.byte	0x4
	.set L$set$40,LCFI21-LCFI20
	.long L$set$40
	.byte	0xe
	.byte	0x30
	.byte	0x86
	.byte	0x6
	.byte	0x4
	.set L$set$41,LCFI22-LCFI21
	.long L$set$41
	.byte	0xe
	.byte	0x38
	.byte	0x83
	.byte	0x7
	.byte	0x4
	.set L$set$42,LCFI23-LCFI22
	.long L$set$42
	.byte	0xe
	.byte	0x90,0x13
	.byte	0x4
	.set L$set$43,LCFI24-LCFI23
	.long L$set$43
	.byte	0xa
	.byte	0xe
	.byte	0x38
	.byte	0x4
	.set L$set$44,LCFI25-LCFI24
	.long L$set$44
	.byte	0xe
	.byte	0x30
	.byte	0x4
	.set L$set$45,LCFI26-LCFI25
	.long L$set$45
	.byte	0xe
	.byte	0x28
	.byte	0x4
	.set L$set$46,LCFI27-LCFI26
	.long L$set$46
	.byte	0xe
	.byte	0x20
	.byte	0x4
	.set L$set$47,LCFI28-LCFI27
	.long L$set$47
	.byte	0xe
	.byte	0x18
	.byte	0x4
	.set L$set$48,LCFI29-LCFI28
	.long L$set$48
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$49,LCFI30-LCFI29
	.long L$set$49
	.byte	0xe
	.byte	0x8
	.byte	0x4
	.set L$set$50,LCFI31-LCFI30
	.long L$set$50
	.byte	0xb
	.align 3
LEFDE10:
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$51,LECIE1-LSCIE1
	.long L$set$51
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.byte	0x1
	.byte	0x78
	.byte	0x10
	.byte	0x1
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.byte	0x90
	.byte	0x1
	.align 3
LECIE1:
LSFDE13:
	.set L$set$52,LEFDE13-LASFDE13
	.long L$set$52
LASFDE13:
	.long	LASFDE13-EH_frame1
	.quad	LFB21-.
	.set L$set$53,LFE21-LFB21
	.quad L$set$53
	.byte	0
	.align 3
LEFDE13:
LSFDE15:
	.set L$set$54,LEFDE15-LASFDE15
	.long L$set$54
LASFDE15:
	.long	LASFDE15-EH_frame1
	.quad	LFB14-.
	.set L$set$55,LFE14-LFB14
	.quad L$set$55
	.byte	0
	.byte	0x4
	.set L$set$56,LCFI0-LFB14
	.long L$set$56
	.byte	0xe
	.byte	0x10
	.byte	0x8c
	.byte	0x2
	.byte	0x4
	.set L$set$57,LCFI1-LCFI0
	.long L$set$57
	.byte	0xe
	.byte	0x18
	.byte	0x86
	.byte	0x3
	.byte	0x4
	.set L$set$58,LCFI2-LCFI1
	.long L$set$58
	.byte	0xe
	.byte	0x20
	.byte	0x83
	.byte	0x4
	.byte	0x4
	.set L$set$59,LCFI3-LCFI2
	.long L$set$59
	.byte	0xe
	.byte	0xf0,0x1
	.align 3
LEFDE15:
LSFDE17:
	.set L$set$60,LEFDE17-LASFDE17
	.long L$set$60
LASFDE17:
	.long	LASFDE17-EH_frame1
	.quad	LFB13-.
	.set L$set$61,LFE13-LFB13
	.quad L$set$61
	.byte	0
	.byte	0x4
	.set L$set$62,LCFI4-LFB13
	.long L$set$62
	.byte	0xe
	.byte	0x10
	.byte	0x8c
	.byte	0x2
	.byte	0x4
	.set L$set$63,LCFI5-LCFI4
	.long L$set$63
	.byte	0xe
	.byte	0x18
	.byte	0x86
	.byte	0x3
	.byte	0x4
	.set L$set$64,LCFI6-LCFI5
	.long L$set$64
	.byte	0xe
	.byte	0x20
	.byte	0x83
	.byte	0x4
	.byte	0x4
	.set L$set$65,LCFI7-LCFI6
	.long L$set$65
	.byte	0xe
	.byte	0xf0,0x1
	.align 3
LEFDE17:
LSFDE19:
	.set L$set$66,LEFDE19-LASFDE19
	.long L$set$66
LASFDE19:
	.long	LASFDE19-EH_frame1
	.quad	LFB3-.
	.set L$set$67,LFE3-LFB3
	.quad L$set$67
	.byte	0
	.byte	0x4
	.set L$set$68,LCFI8-LFB3
	.long L$set$68
	.byte	0xe
	.byte	0x10
	.byte	0x86
	.byte	0x2
	.byte	0x4
	.set L$set$69,LCFI9-LCFI8
	.long L$set$69
	.byte	0xe
	.byte	0x18
	.byte	0x83
	.byte	0x3
	.byte	0x4
	.set L$set$70,LCFI10-LCFI9
	.long L$set$70
	.byte	0xe
	.byte	0x30
	.align 3
LEFDE19:
LSFDE21:
	.set L$set$71,LEFDE21-LASFDE21
	.long L$set$71
LASFDE21:
	.long	LASFDE21-EH_frame1
	.quad	LFB23-.
	.set L$set$72,LFE23-LFB23
	.quad L$set$72
	.byte	0
	.byte	0x4
	.set L$set$73,LCFI11-LFB23
	.long L$set$73
	.byte	0xe
	.byte	0x10
	.byte	0x86
	.byte	0x2
	.byte	0x4
	.set L$set$74,LCFI12-LCFI11
	.long L$set$74
	.byte	0xe
	.byte	0x18
	.byte	0x83
	.byte	0x3
	.byte	0x4
	.set L$set$75,LCFI13-LCFI12
	.long L$set$75
	.byte	0xe
	.byte	0x40
	.byte	0x4
	.set L$set$76,LCFI14-LCFI13
	.long L$set$76
	.byte	0xe
	.byte	0x18
	.byte	0x4
	.set L$set$77,LCFI15-LCFI14
	.long L$set$77
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$78,LCFI16-LCFI15
	.long L$set$78
	.byte	0xe
	.byte	0x8
	.align 3
LEFDE21:
LSFDE23:
	.set L$set$79,LEFDE23-LASFDE23
	.long L$set$79
LASFDE23:
	.long	LASFDE23-EH_frame1
	.quad	LFB22-.
	.set L$set$80,LFE22-LFB22
	.quad L$set$80
	.byte	0
	.byte	0x4
	.set L$set$81,LCFI17-LFB22
	.long L$set$81
	.byte	0xe
	.byte	0x10
	.byte	0x8f
	.byte	0x2
	.byte	0x4
	.set L$set$82,LCFI18-LCFI17
	.long L$set$82
	.byte	0xe
	.byte	0x18
	.byte	0x8e
	.byte	0x3
	.byte	0x4
	.set L$set$83,LCFI19-LCFI18
	.long L$set$83
	.byte	0xe
	.byte	0x20
	.byte	0x8d
	.byte	0x4
	.byte	0x4
	.set L$set$84,LCFI20-LCFI19
	.long L$set$84
	.byte	0xe
	.byte	0x28
	.byte	0x8c
	.byte	0x5
	.byte	0x4
	.set L$set$85,LCFI21-LCFI20
	.long L$set$85
	.byte	0xe
	.byte	0x30
	.byte	0x86
	.byte	0x6
	.byte	0x4
	.set L$set$86,LCFI22-LCFI21
	.long L$set$86
	.byte	0xe
	.byte	0x38
	.byte	0x83
	.byte	0x7
	.byte	0x4
	.set L$set$87,LCFI23-LCFI22
	.long L$set$87
	.byte	0xe
	.byte	0x90,0x13
	.byte	0x4
	.set L$set$88,LCFI24-LCFI23
	.long L$set$88
	.byte	0xa
	.byte	0xe
	.byte	0x38
	.byte	0x4
	.set L$set$89,LCFI25-LCFI24
	.long L$set$89
	.byte	0xe
	.byte	0x30
	.byte	0x4
	.set L$set$90,LCFI26-LCFI25
	.long L$set$90
	.byte	0xe
	.byte	0x28
	.byte	0x4
	.set L$set$91,LCFI27-LCFI26
	.long L$set$91
	.byte	0xe
	.byte	0x20
	.byte	0x4
	.set L$set$92,LCFI28-LCFI27
	.long L$set$92
	.byte	0xe
	.byte	0x18
	.byte	0x4
	.set L$set$93,LCFI29-LCFI28
	.long L$set$93
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$94,LCFI30-LCFI29
	.long L$set$94
	.byte	0xe
	.byte	0x8
	.byte	0x4
	.set L$set$95,LCFI31-LCFI30
	.long L$set$95
	.byte	0xb
	.align 3
LEFDE23:
	.text
Letext0:
	.section __TEXT,__text_cold,regular,pure_instructions
Letext_cold0:
	.section __DWARF,__debug_info,regular,debug
Lsection__debug_info:
Ldebug_info0:
	.long	0x1b54
	.word	0x2
	.set L$set$96,Ldebug_abbrev0-Lsection__debug_abbrev
	.long L$set$96
	.byte	0x8
	.byte	0x1
	.ascii "GNU C11 5.2.0 -fPIC -feliminate-unused-debug-symbols -mmacosx-version-min=10.11.4 -mtune=core2 -g -O3 -std=c11\0"
	.byte	0x1
	.ascii "c_posix.c\0"
	.ascii "/Users/jleffler/soq\0"
	.quad	Ltext0
	.quad	Letext0
	.set L$set$97,Ldebug_line0-Lsection__debug_line
	.long L$set$97
	.byte	0x1
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.ascii "signed char\0"
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.ascii "unsigned char\0"
	.byte	0x2
	.byte	0x2
	.byte	0x5
	.ascii "short int\0"
	.byte	0x3
	.ascii "__uint16_t\0"
	.byte	0x2
	.byte	0x2b
	.long	0xee
	.byte	0x2
	.byte	0x2
	.byte	0x7
	.ascii "short unsigned int\0"
	.byte	0x3
	.ascii "__int32_t\0"
	.byte	0x2
	.byte	0x2c
	.long	0x115
	.byte	0x2
	.byte	0x4
	.byte	0x5
	.ascii "int\0"
	.byte	0x3
	.ascii "__uint32_t\0"
	.byte	0x2
	.byte	0x2d
	.long	0x12e
	.byte	0x2
	.byte	0x4
	.byte	0x7
	.ascii "unsigned int\0"
	.byte	0x3
	.ascii "__int64_t\0"
	.byte	0x2
	.byte	0x2e
	.long	0x14f
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.ascii "long long int\0"
	.byte	0x3
	.ascii "__uint64_t\0"
	.byte	0x2
	.byte	0x2f
	.long	0x172
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.ascii "long long unsigned int\0"
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.ascii "long int\0"
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.ascii "sizetype\0"
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.byte	0x3
	.ascii "__darwin_size_t\0"
	.byte	0x2
	.byte	0x5c
	.long	0x1c3
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.ascii "long unsigned int\0"
	.byte	0x3
	.ascii "__darwin_va_list\0"
	.byte	0x2
	.byte	0x62
	.long	0x1f0
	.byte	0x4
	.long	0x200
	.long	0x200
	.byte	0x5
	.long	0x198
	.byte	0
	.byte	0
	.byte	0x6
	.ascii "__va_list_tag\0"
	.byte	0x18
	.byte	0x3
	.byte	0
	.long	0x273
	.byte	0x7
	.ascii "gp_offset\0"
	.byte	0x3
	.byte	0
	.long	0x12e
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x7
	.ascii "fp_offset\0"
	.byte	0x3
	.byte	0
	.long	0x12e
	.byte	0x2
	.byte	0x23
	.byte	0x4
	.byte	0x7
	.ascii "overflow_arg_area\0"
	.byte	0x3
	.byte	0
	.long	0x273
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0x7
	.ascii "reg_save_area\0"
	.byte	0x3
	.byte	0
	.long	0x273
	.byte	0x2
	.byte	0x23
	.byte	0x10
	.byte	0
	.byte	0x8
	.byte	0x8
	.byte	0x3
	.ascii "__darwin_time_t\0"
	.byte	0x2
	.byte	0x78
	.long	0x18c
	.byte	0x3
	.ascii "__darwin_blkcnt_t\0"
	.byte	0x4
	.byte	0x37
	.long	0x13e
	.byte	0x3
	.ascii "__darwin_blksize_t\0"
	.byte	0x4
	.byte	0x38
	.long	0x104
	.byte	0x3
	.ascii "__darwin_dev_t\0"
	.byte	0x4
	.byte	0x39
	.long	0x104
	.byte	0x3
	.ascii "__darwin_gid_t\0"
	.byte	0x4
	.byte	0x3c
	.long	0x11c
	.byte	0x3
	.ascii "__darwin_ino64_t\0"
	.byte	0x4
	.byte	0x3e
	.long	0x160
	.byte	0x3
	.ascii "__darwin_mode_t\0"
	.byte	0x4
	.byte	0x46
	.long	0xdc
	.byte	0x3
	.ascii "__darwin_off_t\0"
	.byte	0x4
	.byte	0x47
	.long	0x13e
	.byte	0x3
	.ascii "__darwin_pid_t\0"
	.byte	0x4
	.byte	0x48
	.long	0x104
	.byte	0x3
	.ascii "__darwin_sigset_t\0"
	.byte	0x4
	.byte	0x49
	.long	0x11c
	.byte	0x3
	.ascii "__darwin_suseconds_t\0"
	.byte	0x4
	.byte	0x4a
	.long	0x104
	.byte	0x3
	.ascii "__darwin_uid_t\0"
	.byte	0x4
	.byte	0x4b
	.long	0x11c
	.byte	0x3
	.ascii "gid_t\0"
	.byte	0x5
	.byte	0x1e
	.long	0x2d5
	.byte	0x3
	.ascii "size_t\0"
	.byte	0x6
	.byte	0x1e
	.long	0x1ac
	.byte	0x3
	.ascii "uid_t\0"
	.byte	0x7
	.byte	0x1e
	.long	0x37b
	.byte	0x6
	.ascii "passwd\0"
	.byte	0x48
	.byte	0x8
	.byte	0x54
	.long	0x483
	.byte	0x7
	.ascii "pw_name\0"
	.byte	0x8
	.byte	0x55
	.long	0x483
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x7
	.ascii "pw_passwd\0"
	.byte	0x8
	.byte	0x56
	.long	0x483
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0x7
	.ascii "pw_uid\0"
	.byte	0x8
	.byte	0x57
	.long	0x3ac
	.byte	0x2
	.byte	0x23
	.byte	0x10
	.byte	0x7
	.ascii "pw_gid\0"
	.byte	0x8
	.byte	0x58
	.long	0x391
	.byte	0x2
	.byte	0x23
	.byte	0x14
	.byte	0x7
	.ascii "pw_change\0"
	.byte	0x8
	.byte	0x59
	.long	0x275
	.byte	0x2
	.byte	0x23
	.byte	0x18
	.byte	0x7
	.ascii "pw_class\0"
	.byte	0x8
	.byte	0x5a
	.long	0x483
	.byte	0x2
	.byte	0x23
	.byte	0x20
	.byte	0x7
	.ascii "pw_gecos\0"
	.byte	0x8
	.byte	0x5b
	.long	0x483
	.byte	0x2
	.byte	0x23
	.byte	0x28
	.byte	0x7
	.ascii "pw_dir\0"
	.byte	0x8
	.byte	0x5c
	.long	0x483
	.byte	0x2
	.byte	0x23
	.byte	0x30
	.byte	0x7
	.ascii "pw_shell\0"
	.byte	0x8
	.byte	0x5d
	.long	0x483
	.byte	0x2
	.byte	0x23
	.byte	0x38
	.byte	0x7
	.ascii "pw_expire\0"
	.byte	0x8
	.byte	0x5e
	.long	0x275
	.byte	0x2
	.byte	0x23
	.byte	0x40
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x1a4
	.byte	0x4
	.long	0x1a4
	.long	0x499
	.byte	0x5
	.long	0x198
	.byte	0x9
	.byte	0
	.byte	0x4
	.long	0x115
	.long	0x4a9
	.byte	0x5
	.long	0x198
	.byte	0x1
	.byte	0
	.byte	0x3
	.ascii "pid_t\0"
	.byte	0x9
	.byte	0x1e
	.long	0x330
	.byte	0x3
	.ascii "sigset_t\0"
	.byte	0xa
	.byte	0x1e
	.long	0x346
	.byte	0xa
	.ascii "sigval\0"
	.byte	0x8
	.byte	0xb
	.byte	0x9e
	.long	0x4f8
	.byte	0xb
	.ascii "sival_int\0"
	.byte	0xb
	.byte	0xa0
	.long	0x115
	.byte	0xb
	.ascii "sival_ptr\0"
	.byte	0xb
	.byte	0xa1
	.long	0x273
	.byte	0
	.byte	0x6
	.ascii "__siginfo\0"
	.byte	0x68
	.byte	0xb
	.byte	0xb1
	.long	0x5c0
	.byte	0x7
	.ascii "si_signo\0"
	.byte	0xb
	.byte	0xb2
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x7
	.ascii "si_errno\0"
	.byte	0xb
	.byte	0xb3
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0x4
	.byte	0x7
	.ascii "si_code\0"
	.byte	0xb
	.byte	0xb4
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0x7
	.ascii "si_pid\0"
	.byte	0xb
	.byte	0xb5
	.long	0x4a9
	.byte	0x2
	.byte	0x23
	.byte	0xc
	.byte	0x7
	.ascii "si_uid\0"
	.byte	0xb
	.byte	0xb6
	.long	0x3ac
	.byte	0x2
	.byte	0x23
	.byte	0x10
	.byte	0x7
	.ascii "si_status\0"
	.byte	0xb
	.byte	0xb7
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0x14
	.byte	0x7
	.ascii "si_addr\0"
	.byte	0xb
	.byte	0xb8
	.long	0x273
	.byte	0x2
	.byte	0x23
	.byte	0x18
	.byte	0x7
	.ascii "si_value\0"
	.byte	0xb
	.byte	0xb9
	.long	0x4c6
	.byte	0x2
	.byte	0x23
	.byte	0x20
	.byte	0x7
	.ascii "si_band\0"
	.byte	0xb
	.byte	0xba
	.long	0x18c
	.byte	0x2
	.byte	0x23
	.byte	0x28
	.byte	0x7
	.ascii "__pad\0"
	.byte	0xb
	.byte	0xbb
	.long	0x5c0
	.byte	0x2
	.byte	0x23
	.byte	0x30
	.byte	0
	.byte	0x4
	.long	0x1c3
	.long	0x5d0
	.byte	0x5
	.long	0x198
	.byte	0x6
	.byte	0
	.byte	0x3
	.ascii "siginfo_t\0"
	.byte	0xb
	.byte	0xbc
	.long	0x4f8
	.byte	0xc
	.set L$set$98,LASF0-Lsection__debug_str
	.long L$set$98
	.byte	0x8
	.byte	0xb
	.word	0x10d
	.long	0x61b
	.byte	0xd
	.ascii "__sa_handler\0"
	.byte	0xb
	.word	0x10e
	.long	0x627
	.byte	0xd
	.ascii "__sa_sigaction\0"
	.byte	0xb
	.word	0x10f
	.long	0x649
	.byte	0
	.byte	0xe
	.byte	0x1
	.long	0x627
	.byte	0xf
	.long	0x115
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x61b
	.byte	0xe
	.byte	0x1
	.long	0x643
	.byte	0xf
	.long	0x115
	.byte	0xf
	.long	0x643
	.byte	0xf
	.long	0x273
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x4f8
	.byte	0x9
	.byte	0x8
	.long	0x62d
	.byte	0x9
	.byte	0x8
	.long	0x5d0
	.byte	0x10
	.ascii "sigaction\0"
	.byte	0x10
	.byte	0xb
	.word	0x11e
	.long	0x69f
	.byte	0x11
	.set L$set$99,LASF0-Lsection__debug_str
	.long L$set$99
	.byte	0xb
	.word	0x11f
	.long	0x5e1
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x12
	.ascii "sa_mask\0"
	.byte	0xb
	.word	0x120
	.long	0x4b6
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0x12
	.ascii "sa_flags\0"
	.byte	0xb
	.word	0x121
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0xc
	.byte	0
	.byte	0x3
	.ascii "fpos_t\0"
	.byte	0xc
	.byte	0x4d
	.long	0x31a
	.byte	0x6
	.ascii "__sbuf\0"
	.byte	0x10
	.byte	0xc
	.byte	0x58
	.long	0x6dd
	.byte	0x7
	.ascii "_base\0"
	.byte	0xc
	.byte	0x59
	.long	0x6dd
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x7
	.ascii "_size\0"
	.byte	0xc
	.byte	0x5a
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0xbe
	.byte	0x6
	.ascii "__sFILE\0"
	.byte	0x98
	.byte	0xc
	.byte	0x7a
	.long	0x833
	.byte	0x7
	.ascii "_p\0"
	.byte	0xc
	.byte	0x7b
	.long	0x6dd
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x7
	.ascii "_r\0"
	.byte	0xc
	.byte	0x7c
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0x7
	.ascii "_w\0"
	.byte	0xc
	.byte	0x7d
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0xc
	.byte	0x7
	.ascii "_flags\0"
	.byte	0xc
	.byte	0x7e
	.long	0xcf
	.byte	0x2
	.byte	0x23
	.byte	0x10
	.byte	0x7
	.ascii "_file\0"
	.byte	0xc
	.byte	0x7f
	.long	0xcf
	.byte	0x2
	.byte	0x23
	.byte	0x12
	.byte	0x7
	.ascii "_bf\0"
	.byte	0xc
	.byte	0x80
	.long	0x6ad
	.byte	0x2
	.byte	0x23
	.byte	0x18
	.byte	0x7
	.ascii "_lbfsize\0"
	.byte	0xc
	.byte	0x81
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0x28
	.byte	0x7
	.ascii "_cookie\0"
	.byte	0xc
	.byte	0x84
	.long	0x273
	.byte	0x2
	.byte	0x23
	.byte	0x30
	.byte	0x7
	.ascii "_close\0"
	.byte	0xc
	.byte	0x85
	.long	0x843
	.byte	0x2
	.byte	0x23
	.byte	0x38
	.byte	0x7
	.ascii "_read\0"
	.byte	0xc
	.byte	0x86
	.long	0x863
	.byte	0x2
	.byte	0x23
	.byte	0x40
	.byte	0x7
	.ascii "_seek\0"
	.byte	0xc
	.byte	0x87
	.long	0x883
	.byte	0x2
	.byte	0x23
	.byte	0x48
	.byte	0x7
	.ascii "_write\0"
	.byte	0xc
	.byte	0x88
	.long	0x8ae
	.byte	0x2
	.byte	0x23
	.byte	0x50
	.byte	0x7
	.ascii "_ub\0"
	.byte	0xc
	.byte	0x8b
	.long	0x6ad
	.byte	0x2
	.byte	0x23
	.byte	0x58
	.byte	0x7
	.ascii "_extra\0"
	.byte	0xc
	.byte	0x8c
	.long	0x8bf
	.byte	0x2
	.byte	0x23
	.byte	0x68
	.byte	0x7
	.ascii "_ur\0"
	.byte	0xc
	.byte	0x8d
	.long	0x115
	.byte	0x2
	.byte	0x23
	.byte	0x70
	.byte	0x7
	.ascii "_ubuf\0"
	.byte	0xc
	.byte	0x90
	.long	0x8c5
	.byte	0x2
	.byte	0x23
	.byte	0x74
	.byte	0x7
	.ascii "_nbuf\0"
	.byte	0xc
	.byte	0x91
	.long	0x8d5
	.byte	0x2
	.byte	0x23
	.byte	0x77
	.byte	0x7
	.ascii "_lb\0"
	.byte	0xc
	.byte	0x94
	.long	0x6ad
	.byte	0x2
	.byte	0x23
	.byte	0x78
	.byte	0x7
	.ascii "_blksize\0"
	.byte	0xc
	.byte	0x97
	.long	0x115
	.byte	0x3
	.byte	0x23
	.byte	0x88,0x1
	.byte	0x7
	.ascii "_offset\0"
	.byte	0xc
	.byte	0x98
	.long	0x69f
	.byte	0x3
	.byte	0x23
	.byte	0x90,0x1
	.byte	0
	.byte	0x13
	.byte	0x1
	.long	0x115
	.long	0x843
	.byte	0xf
	.long	0x273
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x833
	.byte	0x13
	.byte	0x1
	.long	0x115
	.long	0x863
	.byte	0xf
	.long	0x273
	.byte	0xf
	.long	0x483
	.byte	0xf
	.long	0x115
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x849
	.byte	0x13
	.byte	0x1
	.long	0x69f
	.long	0x883
	.byte	0xf
	.long	0x273
	.byte	0xf
	.long	0x69f
	.byte	0xf
	.long	0x115
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x869
	.byte	0x13
	.byte	0x1
	.long	0x115
	.long	0x8a3
	.byte	0xf
	.long	0x273
	.byte	0xf
	.long	0x8a3
	.byte	0xf
	.long	0x115
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x8a9
	.byte	0x14
	.long	0x1a4
	.byte	0x9
	.byte	0x8
	.long	0x889
	.byte	0x15
	.ascii "__sFILEX\0"
	.byte	0x1
	.byte	0x9
	.byte	0x8
	.long	0x8b4
	.byte	0x4
	.long	0xbe
	.long	0x8d5
	.byte	0x5
	.long	0x198
	.byte	0x2
	.byte	0
	.byte	0x4
	.long	0xbe
	.long	0x8e5
	.byte	0x5
	.long	0x198
	.byte	0
	.byte	0
	.byte	0x3
	.ascii "FILE\0"
	.byte	0xc
	.byte	0x99
	.long	0x6e3
	.byte	0x6
	.ascii "timeval\0"
	.byte	0x10
	.byte	0xd
	.byte	0x1e
	.long	0x925
	.byte	0x7
	.ascii "tv_sec\0"
	.byte	0xd
	.byte	0x20
	.long	0x275
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x7
	.ascii "tv_usec\0"
	.byte	0xd
	.byte	0x21
	.long	0x35f
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0
	.byte	0x3
	.ascii "blkcnt_t\0"
	.byte	0xe
	.byte	0x1e
	.long	0x28c
	.byte	0x3
	.ascii "blksize_t\0"
	.byte	0xf
	.byte	0x1e
	.long	0x2a5
	.byte	0x3
	.ascii "dev_t\0"
	.byte	0x10
	.byte	0x1e
	.long	0x2bf
	.byte	0x3
	.ascii "mode_t\0"
	.byte	0x11
	.byte	0x1e
	.long	0x303
	.byte	0x3
	.ascii "nlink_t\0"
	.byte	0x12
	.byte	0x1e
	.long	0xdc
	.byte	0x3
	.ascii "off_t\0"
	.byte	0x13
	.byte	0x1e
	.long	0x31a
	.byte	0x3
	.ascii "time_t\0"
	.byte	0x14
	.byte	0x1e
	.long	0x275
	.byte	0x6
	.ascii "stat\0"
	.byte	0x90
	.byte	0x15
	.byte	0xb6
	.long	0xb4c
	.byte	0x7
	.ascii "st_dev\0"
	.byte	0x15
	.byte	0xb6
	.long	0x946
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0x7
	.ascii "st_mode\0"
	.byte	0x15
	.byte	0xb6
	.long	0x953
	.byte	0x2
	.byte	0x23
	.byte	0x4
	.byte	0x7
	.ascii "st_nlink\0"
	.byte	0x15
	.byte	0xb6
	.long	0x961
	.byte	0x2
	.byte	0x23
	.byte	0x6
	.byte	0x7
	.ascii "st_ino\0"
	.byte	0x15
	.byte	0xb6
	.long	0x2eb
	.byte	0x2
	.byte	0x23
	.byte	0x8
	.byte	0x7
	.ascii "st_uid\0"
	.byte	0x15
	.byte	0xb6
	.long	0x3ac
	.byte	0x2
	.byte	0x23
	.byte	0x10
	.byte	0x7
	.ascii "st_gid\0"
	.byte	0x15
	.byte	0xb6
	.long	0x391
	.byte	0x2
	.byte	0x23
	.byte	0x14
	.byte	0x7
	.ascii "st_rdev\0"
	.byte	0x15
	.byte	0xb6
	.long	0x946
	.byte	0x2
	.byte	0x23
	.byte	0x18
	.byte	0x7
	.ascii "st_atime\0"
	.byte	0x15
	.byte	0xb6
	.long	0x97d
	.byte	0x2
	.byte	0x23
	.byte	0x20
	.byte	0x7
	.ascii "st_atimensec\0"
	.byte	0x15
	.byte	0xb6
	.long	0x18c
	.byte	0x2
	.byte	0x23
	.byte	0x28
	.byte	0x7
	.ascii "st_mtime\0"
	.byte	0x15
	.byte	0xb6
	.long	0x97d
	.byte	0x2
	.byte	0x23
	.byte	0x30
	.byte	0x7
	.ascii "st_mtimensec\0"
	.byte	0x15
	.byte	0xb6
	.long	0x18c
	.byte	0x2
	.byte	0x23
	.byte	0x38
	.byte	0x7
	.ascii "st_ctime\0"
	.byte	0x15
	.byte	0xb6
	.long	0x97d
	.byte	0x2
	.byte	0x23
	.byte	0x40
	.byte	0x7
	.ascii "st_ctimensec\0"
	.byte	0x15
	.byte	0xb6
	.long	0x18c
	.byte	0x2
	.byte	0x23
	.byte	0x48
	.byte	0x7
	.ascii "st_birthtime\0"
	.byte	0x15
	.byte	0xb6
	.long	0x97d
	.byte	0x2
	.byte	0x23
	.byte	0x50
	.byte	0x7
	.ascii "st_birthtimensec\0"
	.byte	0x15
	.byte	0xb6
	.long	0x18c
	.byte	0x2
	.byte	0x23
	.byte	0x58
	.byte	0x7
	.ascii "st_size\0"
	.byte	0x15
	.byte	0xb6
	.long	0x970
	.byte	0x2
	.byte	0x23
	.byte	0x60
	.byte	0x7
	.ascii "st_blocks\0"
	.byte	0x15
	.byte	0xb6
	.long	0x925
	.byte	0x2
	.byte	0x23
	.byte	0x68
	.byte	0x7
	.ascii "st_blksize\0"
	.byte	0x15
	.byte	0xb6
	.long	0x935
	.byte	0x2
	.byte	0x23
	.byte	0x70
	.byte	0x7
	.ascii "st_flags\0"
	.byte	0x15
	.byte	0xb6
	.long	0x11c
	.byte	0x2
	.byte	0x23
	.byte	0x74
	.byte	0x7
	.ascii "st_gen\0"
	.byte	0x15
	.byte	0xb6
	.long	0x11c
	.byte	0x2
	.byte	0x23
	.byte	0x78
	.byte	0x7
	.ascii "st_lspare\0"
	.byte	0x15
	.byte	0xb6
	.long	0x104
	.byte	0x2
	.byte	0x23
	.byte	0x7c
	.byte	0x7
	.ascii "st_qspare\0"
	.byte	0x15
	.byte	0xb6
	.long	0xb4c
	.byte	0x3
	.byte	0x23
	.byte	0x80,0x1
	.byte	0
	.byte	0x4
	.long	0x13e
	.long	0xb5c
	.byte	0x5
	.long	0x198
	.byte	0x1
	.byte	0
	.byte	0x3
	.ascii "Pipe\0"
	.byte	0x1
	.byte	0x29
	.long	0x499
	.byte	0x6
	.ascii "command\0"
	.byte	0x8
	.byte	0x1
	.byte	0xd5
	.long	0xb88
	.byte	0x7
	.ascii "argv\0"
	.byte	0x1
	.byte	0xd7
	.long	0xb88
	.byte	0x2
	.byte	0x23
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0xb8e
	.byte	0x14
	.long	0x483
	.byte	0x16
	.byte	0x1
	.ascii "__sigbits\0"
	.byte	0x16
	.byte	0x72
	.byte	0x1
	.long	0x115
	.byte	0x3
	.long	0xbbb
	.byte	0x17
	.ascii "__signo\0"
	.byte	0x16
	.byte	0x72
	.long	0x115
	.byte	0
	.byte	0x18
	.ascii "file_exist\0"
	.byte	0x1
	.word	0x15e
	.byte	0x1
	.long	0x115
	.byte	0x1
	.long	0xbf5
	.byte	0x19
	.ascii "filename\0"
	.byte	0x1
	.word	0x15e
	.long	0x483
	.byte	0x1a
	.ascii "buffer\0"
	.byte	0x1
	.word	0x160
	.long	0x98b
	.byte	0
	.byte	0x1b
	.ascii "RemoveSpaces\0"
	.byte	0x1
	.word	0x14f
	.byte	0x1
	.byte	0x1
	.long	0xc30
	.byte	0x19
	.ascii "source\0"
	.byte	0x1
	.word	0x14f
	.long	0x483
	.byte	0x1a
	.ascii "i\0"
	.byte	0x1
	.word	0x151
	.long	0x483
	.byte	0x1a
	.ascii "j\0"
	.byte	0x1
	.word	0x152
	.long	0x483
	.byte	0
	.byte	0x1c
	.ascii "err_setarg0\0"
	.byte	0x1
	.byte	0xb3
	.byte	0x1
	.byte	0x1
	.long	0xc53
	.byte	0x17
	.ascii "argv0\0"
	.byte	0x1
	.byte	0xb3
	.long	0x8a3
	.byte	0
	.byte	0x1c
	.ascii "err_syswarn\0"
	.byte	0x1
	.byte	0xc2
	.byte	0x1
	.byte	0x1
	.long	0xc80
	.byte	0x17
	.ascii "fmt\0"
	.byte	0x1
	.byte	0xc2
	.long	0x8a3
	.byte	0x1d
	.byte	0x1e
	.set L$set$100,LASF1-Lsection__debug_str
	.long L$set$100
	.byte	0x1
	.byte	0xc4
	.long	0x1d8
	.byte	0
	.byte	0x1f
	.set L$set$101,LASF2-Lsection__debug_str
	.long L$set$101
	.byte	0x1
	.byte	0x70
	.byte	0x1
	.byte	0x1
	.long	0xcca
	.byte	0x17
	.ascii "tag\0"
	.byte	0x1
	.byte	0x70
	.long	0x8a3
	.byte	0x17
	.ascii "argc\0"
	.byte	0x1
	.byte	0x70
	.long	0x115
	.byte	0x17
	.ascii "argv\0"
	.byte	0x1
	.byte	0x70
	.long	0xcca
	.byte	0x20
	.set L$set$102,LASF3-Lsection__debug_str
	.long L$set$102
	.long	0xcd0
	.byte	0x1
	.set L$set$103,LASF2-Lsection__debug_str
	.long L$set$103
	.byte	0x21
	.byte	0x22
	.ascii "i\0"
	.byte	0x1
	.byte	0x74
	.long	0x115
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x483
	.byte	0x14
	.long	0x489
	.byte	0x23
	.ascii "StartsWith\0"
	.byte	0x1
	.byte	0xe8
	.byte	0x1
	.long	0x115
	.byte	0x1
	.long	0xd00
	.byte	0x17
	.ascii "a\0"
	.byte	0x1
	.byte	0xe8
	.long	0x8a3
	.byte	0x17
	.ascii "b\0"
	.byte	0x1
	.byte	0xe8
	.long	0x8a3
	.byte	0
	.byte	0x1b
	.ascii "fork_pipes\0"
	.byte	0x1
	.word	0x10d
	.byte	0x1
	.byte	0x1
	.long	0xd4c
	.byte	0x19
	.ascii "n\0"
	.byte	0x1
	.word	0x10d
	.long	0x115
	.byte	0x19
	.ascii "cmd\0"
	.byte	0x1
	.word	0x10d
	.long	0xd4c
	.byte	0x1a
	.ascii "i\0"
	.byte	0x1
	.word	0x10f
	.long	0x115
	.byte	0x1a
	.ascii "in\0"
	.byte	0x1
	.word	0x110
	.long	0x115
	.byte	0x1a
	.ascii "fd\0"
	.byte	0x1
	.word	0x111
	.long	0x499
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0xb68
	.byte	0x1b
	.ascii "Janitor\0"
	.byte	0x1
	.word	0x12d
	.byte	0x1
	.byte	0x1
	.long	0xd8f
	.byte	0x24
	.set L$set$104,LASF4-Lsection__debug_str
	.long L$set$104
	.byte	0x1
	.word	0x12d
	.long	0x115
	.byte	0x21
	.byte	0x1a
	.ascii "a\0"
	.byte	0x1
	.word	0x131
	.long	0x115
	.byte	0x21
	.byte	0x1a
	.ascii "pid_my1\0"
	.byte	0x1
	.word	0x134
	.long	0x4a9
	.byte	0
	.byte	0
	.byte	0
	.byte	0x25
	.ascii "sighandler\0"
	.byte	0x1
	.word	0x166
	.byte	0x1
	.quad	LFB21
	.quad	LFE21
	.byte	0x2
	.byte	0x77
	.byte	0x8
	.long	0xdfc
	.byte	0x26
	.ascii "signo\0"
	.byte	0x1
	.word	0x166
	.long	0x115
	.set L$set$105,LLST0-Lsection__debug_loc
	.long L$set$105
	.byte	0x26
	.ascii "si\0"
	.byte	0x1
	.word	0x166
	.long	0x64f
	.set L$set$106,LLST1-Lsection__debug_loc
	.long L$set$106
	.byte	0x26
	.ascii "vp\0"
	.byte	0x1
	.word	0x166
	.long	0x273
	.set L$set$107,LLST2-Lsection__debug_loc
	.long L$set$107
	.byte	0x1a
	.ascii "return_value\0"
	.byte	0x1
	.word	0x168
	.long	0x115
	.byte	0
	.byte	0x27
	.ascii "err_syserr\0"
	.byte	0x1
	.byte	0xdb
	.byte	0x1
	.quad	LFB14
	.quad	LFE14
	.set L$set$108,LLST3-Lsection__debug_loc
	.long L$set$108
	.long	0xe53
	.byte	0x28
	.ascii "fmt\0"
	.byte	0x1
	.byte	0xdb
	.long	0x483
	.set L$set$109,LLST4-Lsection__debug_loc
	.long L$set$109
	.byte	0x1d
	.byte	0x29
	.ascii "errnum\0"
	.byte	0x1
	.byte	0xdd
	.long	0x115
	.byte	0x1
	.byte	0x53
	.byte	0x2a
	.set L$set$110,LASF1-Lsection__debug_str
	.long L$set$110
	.byte	0x1
	.byte	0xde
	.long	0x1d8
	.byte	0x3
	.byte	0x91
	.byte	0x98,0x7e
	.byte	0
	.byte	0x1c
	.ascii "err_vsyswarn\0"
	.byte	0x1
	.byte	0xb8
	.byte	0x1
	.byte	0x1
	.long	0xe8e
	.byte	0x17
	.ascii "fmt\0"
	.byte	0x1
	.byte	0xb8
	.long	0x8a3
	.byte	0x2b
	.set L$set$111,LASF1-Lsection__debug_str
	.long L$set$111
	.byte	0x1
	.byte	0xb8
	.long	0xe8e
	.byte	0x22
	.ascii "errnum\0"
	.byte	0x1
	.byte	0xba
	.long	0x115
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x200
	.byte	0x27
	.ascii "err_sysexit\0"
	.byte	0x1
	.byte	0xca
	.byte	0x1
	.quad	LFB13
	.quad	LFE13
	.set L$set$112,LLST5-Lsection__debug_loc
	.long L$set$112
	.long	0xf1d
	.byte	0x28
	.ascii "fmt\0"
	.byte	0x1
	.byte	0xca
	.long	0x8a3
	.set L$set$113,LLST6-Lsection__debug_loc
	.long L$set$113
	.byte	0x1d
	.byte	0x2a
	.set L$set$114,LASF1-Lsection__debug_str
	.long L$set$114
	.byte	0x1
	.byte	0xcc
	.long	0x1d8
	.byte	0x3
	.byte	0x91
	.byte	0x98,0x7e
	.byte	0x2c
	.long	0xe53
	.quad	LBB19
	.quad	LBE19
	.byte	0x2d
	.long	0xe74
	.set L$set$115,LLST7-Lsection__debug_loc
	.long L$set$115
	.byte	0x2d
	.long	0xe69
	.set L$set$116,LLST8-Lsection__debug_loc
	.long L$set$116
	.byte	0x2e
	.quad	LBB20
	.quad	LBE20
	.byte	0x2f
	.long	0xe7f
	.byte	0x1
	.byte	0x56
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1f
	.set L$set$117,LASF5-Lsection__debug_str
	.long L$set$117
	.byte	0x1
	.byte	0x4a
	.byte	0x1
	.byte	0x1
	.long	0xf60
	.byte	0x17
	.ascii "ncmds\0"
	.byte	0x1
	.byte	0x4a
	.long	0x115
	.byte	0x17
	.ascii "cmds\0"
	.byte	0x1
	.byte	0x4a
	.long	0xf60
	.byte	0x17
	.ascii "output\0"
	.byte	0x1
	.byte	0x4a
	.long	0xf66
	.byte	0x20
	.set L$set$118,LASF3-Lsection__debug_str
	.long L$set$118
	.long	0xf7c
	.byte	0x1
	.set L$set$119,LASF5-Lsection__debug_str
	.long L$set$119
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0xcca
	.byte	0x9
	.byte	0x8
	.long	0x115
	.byte	0x4
	.long	0x1a4
	.long	0xf7c
	.byte	0x5
	.long	0x198
	.byte	0x11
	.byte	0
	.byte	0x14
	.long	0xf6c
	.byte	0x27
	.ascii "exec_nth_command\0"
	.byte	0x1
	.byte	0x2f
	.byte	0x1
	.quad	LFB3
	.quad	LFE3
	.set L$set$120,LLST9-Lsection__debug_loc
	.long L$set$120
	.long	0x105d
	.byte	0x28
	.ascii "ncmds\0"
	.byte	0x1
	.byte	0x2f
	.long	0x115
	.set L$set$121,LLST10-Lsection__debug_loc
	.long L$set$121
	.byte	0x28
	.ascii "cmds\0"
	.byte	0x1
	.byte	0x2f
	.long	0xf60
	.set L$set$122,LLST11-Lsection__debug_loc
	.long L$set$122
	.byte	0x30
	.set L$set$123,LASF3-Lsection__debug_str
	.long L$set$123
	.long	0x106d
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	___func__.3142
	.byte	0x2e
	.quad	LBB24
	.quad	LBE24
	.byte	0x31
	.ascii "pid\0"
	.byte	0x1
	.byte	0x34
	.long	0x4a9
	.set L$set$124,LLST12-Lsection__debug_loc
	.long L$set$124
	.byte	0x29
	.ascii "input\0"
	.byte	0x1
	.byte	0x35
	.long	0xb5c
	.byte	0x2
	.byte	0x91
	.byte	0x50
	.byte	0x2c
	.long	0xf1d
	.quad	LBB25
	.quad	LBE25
	.byte	0x2d
	.long	0xf43
	.set L$set$125,LLST13-Lsection__debug_loc
	.long L$set$125
	.byte	0x2d
	.long	0xf37
	.set L$set$126,LLST14-Lsection__debug_loc
	.long L$set$126
	.byte	0x2d
	.long	0xf2a
	.set L$set$127,LLST15-Lsection__debug_loc
	.long L$set$127
	.byte	0x2e
	.quad	LBB26
	.quad	LBE26
	.byte	0x32
	.long	0xf51
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x4
	.long	0x1a4
	.long	0x106d
	.byte	0x5
	.long	0x198
	.byte	0x10
	.byte	0
	.byte	0x14
	.long	0x105d
	.byte	0x33
	.long	0xc53
	.quad	LFB23
	.quad	LFE23
	.set L$set$128,LLST16-Lsection__debug_loc
	.long L$set$128
	.long	0x10e2
	.byte	0x2d
	.long	0xc68
	.set L$set$129,LLST17-Lsection__debug_loc
	.long L$set$129
	.byte	0x1d
	.byte	0x2f
	.long	0xc74
	.byte	0x2
	.byte	0x91
	.byte	0x48
	.byte	0x34
	.long	0xc68
	.byte	0x2c
	.long	0xe53
	.quad	LBB31
	.quad	LBE31
	.byte	0x34
	.long	0xe74
	.byte	0x34
	.long	0xe69
	.byte	0x2e
	.quad	LBB32
	.quad	LBE32
	.byte	0x35
	.long	0xe7f
	.set L$set$130,LLST18-Lsection__debug_loc
	.long L$set$130
	.byte	0
	.byte	0
	.byte	0
	.byte	0x23
	.ascii "spawn_proc\0"
	.byte	0x1
	.byte	0xf0
	.byte	0x1
	.long	0x115
	.byte	0x1
	.long	0x1126
	.byte	0x17
	.ascii "in\0"
	.byte	0x1
	.byte	0xf0
	.long	0x115
	.byte	0x17
	.ascii "out\0"
	.byte	0x1
	.byte	0xf0
	.long	0x115
	.byte	0x17
	.ascii "cmd\0"
	.byte	0x1
	.byte	0xf0
	.long	0xd4c
	.byte	0x22
	.ascii "pid\0"
	.byte	0x1
	.byte	0xf2
	.long	0x4a9
	.byte	0
	.byte	0x1c
	.ascii "corpse_collector\0"
	.byte	0x1
	.byte	0x62
	.byte	0x1
	.byte	0x1
	.long	0x1168
	.byte	0x22
	.ascii "parent\0"
	.byte	0x1
	.byte	0x64
	.long	0x4a9
	.byte	0x22
	.ascii "corpse\0"
	.byte	0x1
	.byte	0x65
	.long	0x4a9
	.byte	0x1e
	.set L$set$131,LASF4-Lsection__debug_str
	.long L$set$131
	.byte	0x1
	.byte	0x66
	.long	0x115
	.byte	0
	.byte	0x1c
	.ascii "exec_arguments\0"
	.byte	0x1
	.byte	0x8a
	.byte	0x1
	.byte	0x1
	.long	0x11e0
	.byte	0x17
	.ascii "argc\0"
	.byte	0x1
	.byte	0x8a
	.long	0x115
	.byte	0x17
	.ascii "argv\0"
	.byte	0x1
	.byte	0x8a
	.long	0xcca
	.byte	0x22
	.ascii "cmdv\0"
	.byte	0x1
	.byte	0x90
	.long	0xf60
	.byte	0x1e
	.set L$set$132,LASF1-Lsection__debug_str
	.long L$set$132
	.byte	0x1
	.byte	0x91
	.long	0xcca
	.byte	0x22
	.ascii "cmdn\0"
	.byte	0x1
	.byte	0x92
	.long	0x115
	.byte	0x22
	.ascii "argn\0"
	.byte	0x1
	.byte	0x93
	.long	0x115
	.byte	0x21
	.byte	0x22
	.ascii "i\0"
	.byte	0x1
	.byte	0x97
	.long	0x115
	.byte	0x21
	.byte	0x22
	.ascii "arg\0"
	.byte	0x1
	.byte	0x99
	.long	0x483
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1f
	.set L$set$133,LASF6-Lsection__debug_str
	.long L$set$133
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x1
	.long	0x1220
	.byte	0x17
	.ascii "ncmds\0"
	.byte	0x1
	.byte	0x55
	.long	0x115
	.byte	0x17
	.ascii "cmds\0"
	.byte	0x1
	.byte	0x55
	.long	0xf60
	.byte	0x22
	.ascii "pid\0"
	.byte	0x1
	.byte	0x57
	.long	0x4a9
	.byte	0x20
	.set L$set$134,LASF3-Lsection__debug_str
	.long L$set$134
	.long	0x1230
	.byte	0x1
	.set L$set$135,LASF6-Lsection__debug_str
	.long L$set$135
	.byte	0
	.byte	0x4
	.long	0x1a4
	.long	0x1230
	.byte	0x5
	.long	0x198
	.byte	0xd
	.byte	0
	.byte	0x14
	.long	0x1220
	.byte	0x1c
	.ascii "dump_pipeline\0"
	.byte	0x1
	.byte	0x7b
	.byte	0x1
	.byte	0x1
	.long	0x127d
	.byte	0x17
	.ascii "cmdn\0"
	.byte	0x1
	.byte	0x7b
	.long	0x115
	.byte	0x17
	.ascii "cmdv\0"
	.byte	0x1
	.byte	0x7b
	.long	0xf60
	.byte	0x21
	.byte	0x22
	.ascii "i\0"
	.byte	0x1
	.byte	0x7e
	.long	0x115
	.byte	0x21
	.byte	0x1e
	.set L$set$136,LASF1-Lsection__debug_str
	.long L$set$136
	.byte	0x1
	.byte	0x81
	.long	0xcca
	.byte	0
	.byte	0
	.byte	0
	.byte	0x36
	.byte	0x1
	.ascii "main\0"
	.byte	0x1
	.word	0x16d
	.byte	0x1
	.long	0x115
	.quad	LFB22
	.quad	LFE22
	.set L$set$137,LLST19-Lsection__debug_loc
	.long L$set$137
	.long	0x1a64
	.byte	0x26
	.ascii "argc\0"
	.byte	0x1
	.word	0x16d
	.long	0x115
	.set L$set$138,LLST20-Lsection__debug_loc
	.long L$set$138
	.byte	0x26
	.ascii "argv\0"
	.byte	0x1
	.word	0x16d
	.long	0xcca
	.set L$set$139,LLST21-Lsection__debug_loc
	.long L$set$139
	.byte	0x37
	.ascii "p\0"
	.byte	0x1
	.word	0x16f
	.long	0x483
	.set L$set$140,LLST22-Lsection__debug_loc
	.long L$set$140
	.byte	0x38
	.ascii "array\0"
	.byte	0x1
	.word	0x170
	.long	0x1a64
	.byte	0x3
	.byte	0x91
	.byte	0xe0,0x6e
	.byte	0x38
	.ascii "line\0"
	.byte	0x1
	.word	0x171
	.long	0x1a74
	.byte	0x3
	.byte	0x91
	.byte	0xc0,0x6f
	.byte	0x38
	.ascii "line2\0"
	.byte	0x1
	.word	0x172
	.long	0x1a74
	.byte	0x3
	.byte	0x91
	.byte	0xc0,0x77
	.byte	0x1a
	.ascii "argv2\0"
	.byte	0x1
	.word	0x173
	.long	0x1a85
	.byte	0x39
	.ascii "argc2\0"
	.byte	0x1
	.word	0x174
	.long	0x115
	.byte	0
	.byte	0x37
	.ascii "length\0"
	.byte	0x1
	.word	0x175
	.long	0x39e
	.set L$set$141,LLST23-Lsection__debug_loc
	.long L$set$141
	.byte	0x37
	.ascii "token3\0"
	.byte	0x1
	.word	0x176
	.long	0x483
	.set L$set$142,LLST24-Lsection__debug_loc
	.long L$set$142
	.byte	0x37
	.ascii "i\0"
	.byte	0x1
	.word	0x177
	.long	0x115
	.set L$set$143,LLST25-Lsection__debug_loc
	.long L$set$143
	.byte	0x37
	.ascii "tokenstr\0"
	.byte	0x1
	.word	0x178
	.long	0x483
	.set L$set$144,LLST26-Lsection__debug_loc
	.long L$set$144
	.byte	0x1a
	.ascii "search\0"
	.byte	0x1
	.word	0x179
	.long	0x483
	.byte	0x37
	.ascii "isBackground\0"
	.byte	0x1
	.word	0x17a
	.long	0x115
	.set L$set$145,LLST27-Lsection__debug_loc
	.long L$set$145
	.byte	0x1a
	.ascii "built_in_command\0"
	.byte	0x1
	.word	0x17b
	.long	0x115
	.byte	0x38
	.ascii "fd\0"
	.byte	0x1
	.word	0x17c
	.long	0x499
	.byte	0x3
	.byte	0x91
	.byte	0xd0,0x6d
	.byte	0x38
	.ascii "printenv\0"
	.byte	0x1
	.word	0x17d
	.long	0x1a95
	.byte	0x3
	.byte	0x91
	.byte	0xf0,0x6d
	.byte	0x38
	.ascii "sort\0"
	.byte	0x1
	.word	0x17e
	.long	0x1a95
	.byte	0x3
	.byte	0x91
	.byte	0x80,0x6e
	.byte	0x38
	.ascii "pager_cmd\0"
	.byte	0x1
	.word	0x17f
	.long	0x1a95
	.byte	0x3
	.byte	0x91
	.byte	0x90,0x6e
	.byte	0x38
	.ascii "grep\0"
	.byte	0x1
	.word	0x180
	.long	0x1a64
	.byte	0x3
	.byte	0x91
	.byte	0x80,0x6f
	.byte	0x37
	.ascii "time\0"
	.byte	0x1
	.word	0x181
	.long	0x18c
	.set L$set$146,LLST28-Lsection__debug_loc
	.long L$set$146
	.byte	0x3a
	.set L$set$147,LASF4-Lsection__debug_str
	.long L$set$147
	.byte	0x1
	.word	0x182
	.long	0x115
	.byte	0x3
	.byte	0x91
	.byte	0xbc,0x6d
	.byte	0x39
	.ascii "max\0"
	.byte	0x1
	.word	0x183
	.long	0x115
	.byte	0x50
	.byte	0x1a
	.ascii "b\0"
	.byte	0x1
	.word	0x184
	.long	0x115
	.byte	0x39
	.ascii "pos\0"
	.byte	0x1
	.word	0x185
	.long	0x115
	.byte	0
	.byte	0x37
	.ascii "tmp\0"
	.byte	0x1
	.word	0x186
	.long	0x483
	.set L$set$148,LLST29-Lsection__debug_loc
	.long L$set$148
	.byte	0x37
	.ascii "new_str\0"
	.byte	0x1
	.word	0x187
	.long	0x483
	.set L$set$149,LLST30-Lsection__debug_loc
	.long L$set$149
	.byte	0x39
	.ascii "len\0"
	.byte	0x1
	.word	0x188
	.long	0x115
	.byte	0x1
	.byte	0x1a
	.ascii "k\0"
	.byte	0x1
	.word	0x189
	.long	0x115
	.byte	0x37
	.ascii "pw\0"
	.byte	0x1
	.word	0x18a
	.long	0x1aa5
	.set L$set$150,LLST31-Lsection__debug_loc
	.long L$set$150
	.byte	0x37
	.ascii "homedir\0"
	.byte	0x1
	.word	0x18b
	.long	0x8a3
	.set L$set$151,LLST32-Lsection__debug_loc
	.long L$set$151
	.byte	0x1a
	.ascii "cmd\0"
	.byte	0x1
	.word	0x18c
	.long	0x1aab
	.byte	0x38
	.ascii "cmd2\0"
	.byte	0x1
	.word	0x18d
	.long	0x1abb
	.byte	0x3
	.byte	0x91
	.byte	0xa0,0x6f
	.byte	0x38
	.ascii "time_start\0"
	.byte	0x1
	.word	0x18e
	.long	0x8f1
	.byte	0x3
	.byte	0x91
	.byte	0xa0,0x6e
	.byte	0x38
	.ascii "time_end\0"
	.byte	0x1
	.word	0x18f
	.long	0x8f1
	.byte	0x3
	.byte	0x91
	.byte	0xb0,0x6e
	.byte	0x38
	.ascii "my_sig\0"
	.byte	0x1
	.word	0x190
	.long	0x4b6
	.byte	0x3
	.byte	0x91
	.byte	0xc0,0x6d
	.byte	0x37
	.ascii "pid_temp\0"
	.byte	0x1
	.word	0x191
	.long	0x4a9
	.set L$set$152,LLST33-Lsection__debug_loc
	.long L$set$152
	.byte	0x37
	.ascii "pagerValue\0"
	.byte	0x1
	.word	0x192
	.long	0x483
	.set L$set$153,LLST34-Lsection__debug_loc
	.long L$set$153
	.byte	0x37
	.ascii "ret\0"
	.byte	0x1
	.word	0x193
	.long	0x115
	.set L$set$154,LLST35-Lsection__debug_loc
	.long L$set$154
	.byte	0x37
	.ascii "pathValue\0"
	.byte	0x1
	.word	0x194
	.long	0x483
	.set L$set$155,LLST36-Lsection__debug_loc
	.long L$set$155
	.byte	0x37
	.ascii "pathValue2\0"
	.byte	0x1
	.word	0x195
	.long	0x483
	.set L$set$156,LLST37-Lsection__debug_loc
	.long L$set$156
	.byte	0x1a
	.ascii "breakloop\0"
	.byte	0x1
	.word	0x196
	.long	0x115
	.byte	0x38
	.ascii "sa\0"
	.byte	0x1
	.word	0x197
	.long	0x655
	.byte	0x3
	.byte	0x91
	.byte	0xc0,0x6e
	.byte	0x38
	.ascii "osa\0"
	.byte	0x1
	.word	0x197
	.long	0x655
	.byte	0x3
	.byte	0x91
	.byte	0xd0,0x6e
	.byte	0x3b
	.long	0xbbb
	.quad	LBB77
	.quad	LBE77
	.long	0x15e3
	.byte	0x2d
	.long	0xbd4
	.set L$set$157,LLST38-Lsection__debug_loc
	.long L$set$157
	.byte	0x2e
	.quad	LBB78
	.quad	LBE78
	.byte	0x2f
	.long	0xbe5
	.byte	0x3
	.byte	0x91
	.byte	0xc0,0x77
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0xd52
	.quad	LBB83
	.quad	LBE83
	.long	0x1638
	.byte	0x2d
	.long	0xd64
	.set L$set$158,LLST39-Lsection__debug_loc
	.long L$set$158
	.byte	0x2e
	.quad	LBB84
	.quad	LBE84
	.byte	0x32
	.long	0xd71
	.byte	0x2e
	.quad	LBB85
	.quad	LBE85
	.byte	0x35
	.long	0xd7c
	.set L$set$159,LLST40-Lsection__debug_loc
	.long L$set$159
	.byte	0
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0xd52
	.quad	LBB86
	.quad	LBE86
	.long	0x168d
	.byte	0x2d
	.long	0xd64
	.set L$set$160,LLST41-Lsection__debug_loc
	.long L$set$160
	.byte	0x2e
	.quad	LBB87
	.quad	LBE87
	.byte	0x32
	.long	0xd71
	.byte	0x2e
	.quad	LBB88
	.quad	LBE88
	.byte	0x35
	.long	0xd7c
	.set L$set$161,LLST42-Lsection__debug_loc
	.long L$set$161
	.byte	0
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0xbf5
	.quad	LBB89
	.quad	LBE89
	.long	0x16d4
	.byte	0x2d
	.long	0xc0c
	.set L$set$162,LLST43-Lsection__debug_loc
	.long L$set$162
	.byte	0x2e
	.quad	LBB90
	.quad	LBE90
	.byte	0x35
	.long	0xc1b
	.set L$set$163,LLST44-Lsection__debug_loc
	.long L$set$163
	.byte	0x35
	.long	0xc25
	.set L$set$164,LLST45-Lsection__debug_loc
	.long L$set$164
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0xcd5
	.quad	LBB91
	.quad	LBE91
	.long	0x16fc
	.byte	0x34
	.long	0xcf6
	.byte	0x2d
	.long	0xced
	.set L$set$165,LLST46-Lsection__debug_loc
	.long L$set$165
	.byte	0
	.byte	0x3b
	.long	0xcd5
	.quad	LBB95
	.quad	LBE95
	.long	0x1720
	.byte	0x34
	.long	0xcf6
	.byte	0x34
	.long	0xced
	.byte	0
	.byte	0x3b
	.long	0xcd5
	.quad	LBB97
	.quad	LBE97
	.long	0x1744
	.byte	0x34
	.long	0xcf6
	.byte	0x34
	.long	0xced
	.byte	0
	.byte	0x3b
	.long	0xc30
	.quad	LBB100
	.quad	LBE100
	.long	0x1767
	.byte	0x2d
	.long	0xc45
	.set L$set$166,LLST47-Lsection__debug_loc
	.long L$set$166
	.byte	0
	.byte	0x3b
	.long	0x1168
	.quad	LBB104
	.quad	LBE104
	.long	0x1912
	.byte	0x2d
	.long	0x118c
	.set L$set$167,LLST48-Lsection__debug_loc
	.long L$set$167
	.byte	0x2d
	.long	0x1180
	.set L$set$168,LLST49-Lsection__debug_loc
	.long L$set$168
	.byte	0x2e
	.quad	LBB105
	.quad	LBE105
	.byte	0x35
	.long	0x1198
	.set L$set$169,LLST50-Lsection__debug_loc
	.long L$set$169
	.byte	0x35
	.long	0x11a4
	.set L$set$170,LLST51-Lsection__debug_loc
	.long L$set$170
	.byte	0x35
	.long	0x11af
	.set L$set$171,LLST52-Lsection__debug_loc
	.long L$set$171
	.byte	0x32
	.long	0x11bb
	.byte	0x3b
	.long	0xc80
	.quad	LBB106
	.quad	LBE106
	.long	0x1830
	.byte	0x34
	.long	0xc8d
	.byte	0x2d
	.long	0xca4
	.set L$set$172,LLST48-Lsection__debug_loc
	.long L$set$172
	.byte	0x2d
	.long	0xc98
	.set L$set$173,LLST49-Lsection__debug_loc
	.long L$set$173
	.byte	0x2e
	.quad	LBB107
	.quad	LBE107
	.byte	0x2f
	.long	0xcb0
	.byte	0x9
	.byte	0x3
	.quad	___func__.3171
	.byte	0x2e
	.quad	LBB108
	.quad	LBE108
	.byte	0x35
	.long	0xcbf
	.set L$set$174,LLST55-Lsection__debug_loc
	.long L$set$174
	.byte	0
	.byte	0
	.byte	0
	.byte	0x3c
	.quad	LBB114
	.quad	LBE114
	.long	0x1866
	.byte	0x32
	.long	0x11c8
	.byte	0x2e
	.quad	LBB115
	.quad	LBE115
	.byte	0x35
	.long	0x11d2
	.set L$set$175,LLST56-Lsection__debug_loc
	.long L$set$175
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0x1235
	.quad	LBB123
	.quad	LBE123
	.long	0x18c8
	.byte	0x2d
	.long	0x1258
	.set L$set$176,LLST57-Lsection__debug_loc
	.long L$set$176
	.byte	0x2d
	.long	0x124c
	.set L$set$177,LLST58-Lsection__debug_loc
	.long L$set$177
	.byte	0x2e
	.quad	LBB125
	.quad	LBE125
	.byte	0x35
	.long	0x1265
	.set L$set$178,LLST59-Lsection__debug_loc
	.long L$set$178
	.byte	0x2e
	.quad	LBB126
	.quad	LBE126
	.byte	0x35
	.long	0x126f
	.set L$set$179,LLST60-Lsection__debug_loc
	.long L$set$179
	.byte	0
	.byte	0
	.byte	0
	.byte	0x2c
	.long	0x11e0
	.quad	LBB127
	.quad	LBE127
	.byte	0x2d
	.long	0x11fa
	.set L$set$180,LLST61-Lsection__debug_loc
	.long L$set$180
	.byte	0x2d
	.long	0x11ed
	.set L$set$181,LLST62-Lsection__debug_loc
	.long L$set$181
	.byte	0x2e
	.quad	LBB128
	.quad	LBE128
	.byte	0x35
	.long	0x1206
	.set L$set$182,LLST63-Lsection__debug_loc
	.long L$set$182
	.byte	0x32
	.long	0x1211
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0xd00
	.quad	LBB146
	.quad	LBE146
	.long	0x19af
	.byte	0x34
	.long	0xd15
	.byte	0x2d
	.long	0xd1f
	.set L$set$183,LLST64-Lsection__debug_loc
	.long L$set$183
	.byte	0x2e
	.quad	LBB147
	.quad	LBE147
	.byte	0x35
	.long	0xd2b
	.set L$set$184,LLST65-Lsection__debug_loc
	.long L$set$184
	.byte	0x35
	.long	0xd35
	.set L$set$185,LLST66-Lsection__debug_loc
	.long L$set$185
	.byte	0x2f
	.long	0xd40
	.byte	0x3
	.byte	0x91
	.byte	0xe0,0x6d
	.byte	0x2c
	.long	0x10e2
	.quad	LBB148
	.quad	LBE148
	.byte	0x34
	.long	0x110f
	.byte	0x2d
	.long	0x1104
	.set L$set$186,LLST67-Lsection__debug_loc
	.long L$set$186
	.byte	0x2d
	.long	0x10fa
	.set L$set$187,LLST68-Lsection__debug_loc
	.long L$set$187
	.byte	0x2e
	.quad	LBB149
	.quad	LBE149
	.byte	0x35
	.long	0x111a
	.set L$set$188,LLST69-Lsection__debug_loc
	.long L$set$188
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0x1126
	.quad	LBB167
	.quad	LBE167
	.long	0x19f6
	.byte	0x2e
	.quad	LBB168
	.quad	LBE168
	.byte	0x35
	.long	0x1140
	.set L$set$189,LLST70-Lsection__debug_loc
	.long L$set$189
	.byte	0x35
	.long	0x114e
	.set L$set$190,LLST71-Lsection__debug_loc
	.long L$set$190
	.byte	0x2f
	.long	0x115c
	.byte	0x3
	.byte	0x91
	.byte	0xa0,0x6f
	.byte	0
	.byte	0
	.byte	0x2e
	.quad	LBB169
	.quad	LBE169
	.byte	0x1a
	.ascii "a\0"
	.byte	0x1
	.word	0x296
	.long	0x115
	.byte	0x2c
	.long	0xd52
	.quad	LBB170
	.quad	LBE170
	.byte	0x2d
	.long	0xd64
	.set L$set$191,LLST72-Lsection__debug_loc
	.long L$set$191
	.byte	0x2e
	.quad	LBB171
	.quad	LBE171
	.byte	0x32
	.long	0xd71
	.byte	0x2e
	.quad	LBB172
	.quad	LBE172
	.byte	0x35
	.long	0xd7c
	.set L$set$192,LLST73-Lsection__debug_loc
	.long L$set$192
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x4
	.long	0x483
	.long	0x1a74
	.byte	0x5
	.long	0x198
	.byte	0x3
	.byte	0
	.byte	0x4
	.long	0x1a4
	.long	0x1a85
	.byte	0x3d
	.long	0x198
	.word	0x3ff
	.byte	0
	.byte	0x4
	.long	0x483
	.long	0x1a95
	.byte	0x5
	.long	0x198
	.byte	0x63
	.byte	0
	.byte	0x4
	.long	0x483
	.long	0x1aa5
	.byte	0x5
	.long	0x198
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x3b9
	.byte	0x4
	.long	0xb68
	.long	0x1abb
	.byte	0x5
	.long	0x198
	.byte	0x2
	.byte	0
	.byte	0x4
	.long	0xb68
	.long	0x1acb
	.byte	0x5
	.long	0x198
	.byte	0x3
	.byte	0
	.byte	0x29
	.ascii "arg0\0"
	.byte	0x1
	.byte	0xb1
	.long	0x8a3
	.byte	0x9
	.byte	0x3
	.quad	_arg0
	.byte	0x3e
	.ascii "__stdinp\0"
	.byte	0xc
	.byte	0x9c
	.long	0x1af3
	.byte	0x1
	.byte	0x1
	.byte	0x9
	.byte	0x8
	.long	0x8e5
	.byte	0x3e
	.ascii "__stdoutp\0"
	.byte	0xc
	.byte	0x9d
	.long	0x1af3
	.byte	0x1
	.byte	0x1
	.byte	0x3e
	.ascii "__stderrp\0"
	.byte	0xc
	.byte	0x9e
	.long	0x1af3
	.byte	0x1
	.byte	0x1
	.byte	0x3f
	.ascii "isSignal\0"
	.byte	0x1
	.byte	0x1b
	.long	0x115
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	_isSignal
	.byte	0x3f
	.ascii "foreground\0"
	.byte	0x1
	.byte	0xd3
	.long	0x4a9
	.byte	0x1
	.byte	0x9
	.byte	0x3
	.quad	_foreground
	.byte	0
	.section __DWARF,__debug_abbrev,regular,debug
Lsection__debug_abbrev:
Ldebug_abbrev0:
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0x8
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0x1b
	.byte	0x8
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x10
	.byte	0x6
	.byte	0xb4,0x42
	.byte	0xc
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0x1
	.byte	0x1
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x13
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x38
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x8
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xa
	.byte	0x17
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xb
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xc
	.byte	0x17
	.byte	0x1
	.byte	0x3
	.byte	0xe
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xd
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xe
	.byte	0x15
	.byte	0x1
	.byte	0x27
	.byte	0xc
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xf
	.byte	0x5
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x10
	.byte	0x13
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x11
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0x38
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x12
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0x38
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x13
	.byte	0x15
	.byte	0x1
	.byte	0x27
	.byte	0xc
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x14
	.byte	0x26
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x15
	.byte	0x13
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3c
	.byte	0xc
	.byte	0
	.byte	0
	.byte	0x16
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0xc
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x27
	.byte	0xc
	.byte	0x49
	.byte	0x13
	.byte	0x20
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x17
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x18
	.byte	0x2e
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x27
	.byte	0xc
	.byte	0x49
	.byte	0x13
	.byte	0x20
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x19
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x1a
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x1b
	.byte	0x2e
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x27
	.byte	0xc
	.byte	0x20
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x1c
	.byte	0x2e
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x27
	.byte	0xc
	.byte	0x20
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x1d
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1e
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x1f
	.byte	0x2e
	.byte	0x1
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x27
	.byte	0xc
	.byte	0x20
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x20
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x49
	.byte	0x13
	.byte	0x34
	.byte	0xc
	.byte	0x1c
	.byte	0xe
	.byte	0
	.byte	0
	.byte	0x21
	.byte	0xb
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x22
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x23
	.byte	0x2e
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x27
	.byte	0xc
	.byte	0x49
	.byte	0x13
	.byte	0x20
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x24
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x25
	.byte	0x2e
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x27
	.byte	0xc
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x40
	.byte	0xa
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x26
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0x27
	.byte	0x2e
	.byte	0x1
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x27
	.byte	0xc
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x40
	.byte	0x6
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x28
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0x29
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x2a
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x2b
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x2c
	.byte	0x1d
	.byte	0x1
	.byte	0x31
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x2d
	.byte	0x5
	.byte	0
	.byte	0x31
	.byte	0x13
	.byte	0x2
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0x2e
	.byte	0xb
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x2f
	.byte	0x34
	.byte	0
	.byte	0x31
	.byte	0x13
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x30
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x49
	.byte	0x13
	.byte	0x34
	.byte	0xc
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x31
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0x32
	.byte	0x34
	.byte	0
	.byte	0x31
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x33
	.byte	0x2e
	.byte	0x1
	.byte	0x31
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x40
	.byte	0x6
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x34
	.byte	0x5
	.byte	0
	.byte	0x31
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x35
	.byte	0x34
	.byte	0
	.byte	0x31
	.byte	0x13
	.byte	0x2
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0x36
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0xc
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x27
	.byte	0xc
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x40
	.byte	0x6
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x37
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x6
	.byte	0
	.byte	0
	.byte	0x38
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x39
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0x1c
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0x3a
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x3b
	.byte	0x1d
	.byte	0x1
	.byte	0x31
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x3c
	.byte	0xb
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x1
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x3d
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0x5
	.byte	0
	.byte	0
	.byte	0x3e
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3f
	.byte	0xc
	.byte	0x3c
	.byte	0xc
	.byte	0
	.byte	0
	.byte	0x3f
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x3f
	.byte	0xc
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0
	.section __DWARF,__debug_loc,regular,debug
Lsection__debug_loc:
Ldebug_loc0:
LLST0:
	.quad	LVL0
	.quad	LVL2
	.word	0x1
	.byte	0x55
	.quad	0
	.quad	0
LLST1:
	.quad	LVL0
	.quad	LVL3
	.word	0x1
	.byte	0x54
	.quad	0
	.quad	0
LLST2:
	.quad	LVL0
	.quad	LVL1
	.word	0x1
	.byte	0x51
	.quad	0
	.quad	0
LLST3:
	.quad	LFB14
	.quad	LCFI0
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI0
	.quad	LCFI1
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	LCFI1
	.quad	LCFI2
	.word	0x2
	.byte	0x77
	.byte	0x18
	.quad	LCFI2
	.quad	LCFI3
	.word	0x2
	.byte	0x77
	.byte	0x20
	.quad	LCFI3
	.quad	LFE14
	.word	0x3
	.byte	0x77
	.byte	0xf0,0x1
	.quad	0
	.quad	0
LLST4:
	.quad	LVL5
	.quad	LVL6-1
	.word	0x1
	.byte	0x55
	.quad	LVL6-1
	.quad	LFE14
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST5:
	.quad	LFB13
	.quad	LCFI4
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI4
	.quad	LCFI5
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	LCFI5
	.quad	LCFI6
	.word	0x2
	.byte	0x77
	.byte	0x18
	.quad	LCFI6
	.quad	LCFI7
	.word	0x2
	.byte	0x77
	.byte	0x20
	.quad	LCFI7
	.quad	LFE13
	.word	0x3
	.byte	0x77
	.byte	0xf0,0x1
	.quad	0
	.quad	0
LLST6:
	.quad	LVL12
	.quad	LVL14-1
	.word	0x1
	.byte	0x55
	.quad	LVL14-1
	.quad	LFE13
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST7:
	.quad	LVL18
	.quad	LVL19-1
	.word	0x1
	.byte	0x51
	.quad	0
	.quad	0
LLST8:
	.quad	LVL13
	.quad	LVL14-1
	.word	0x1
	.byte	0x55
	.quad	LVL14-1
	.quad	LFE13
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST9:
	.quad	LFB3
	.quad	LCFI8
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI8
	.quad	LCFI9
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	LCFI9
	.quad	LCFI10
	.word	0x2
	.byte	0x77
	.byte	0x18
	.quad	LCFI10
	.quad	LFE3
	.word	0x2
	.byte	0x77
	.byte	0x30
	.quad	0
	.quad	0
LLST10:
	.quad	LVL24
	.quad	LVL25
	.word	0x1
	.byte	0x55
	.quad	LVL25
	.quad	LVL31
	.word	0x1
	.byte	0x53
	.quad	LVL34
	.quad	LVL36
	.word	0x1
	.byte	0x55
	.quad	LVL36
	.quad	LFE3
	.word	0x1
	.byte	0x53
	.quad	0
	.quad	0
LLST11:
	.quad	LVL24
	.quad	LVL26-1
	.word	0x1
	.byte	0x54
	.quad	LVL26-1
	.quad	LVL34
	.word	0x1
	.byte	0x56
	.quad	LVL34
	.quad	LVL35
	.word	0x1
	.byte	0x54
	.quad	LVL37
	.quad	LFE3
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST12:
	.quad	LVL27
	.quad	LVL28-1
	.word	0x1
	.byte	0x50
	.quad	LVL37
	.quad	LVL38-1
	.word	0x1
	.byte	0x50
	.quad	LVL42
	.quad	LVL43
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST13:
	.quad	LVL37
	.quad	LVL42
	.word	0x1
	.byte	0x57
	.quad	0
	.quad	0
LLST14:
	.quad	LVL37
	.quad	LVL42
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST15:
	.quad	LVL41
	.quad	LVL42-1
	.word	0x1
	.byte	0x55
	.quad	0
	.quad	0
LLST16:
	.quad	LFB23
	.quad	LCFI11
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI11
	.quad	LCFI12
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	LCFI12
	.quad	LCFI13
	.word	0x2
	.byte	0x77
	.byte	0x18
	.quad	LCFI13
	.quad	LCFI14
	.word	0x3
	.byte	0x77
	.byte	0xc0,0
	.quad	LCFI14
	.quad	LCFI15
	.word	0x2
	.byte	0x77
	.byte	0x18
	.quad	LCFI15
	.quad	LCFI16
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	LCFI16
	.quad	LFE23
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	0
	.quad	0
LLST17:
	.quad	LVL45
	.quad	LVL47-1
	.word	0x1
	.byte	0x55
	.quad	0
	.quad	0
LLST18:
	.quad	LVL48
	.quad	LVL55
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST19:
	.quad	LFB22
	.quad	LCFI17
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI17
	.quad	LCFI18
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	LCFI18
	.quad	LCFI19
	.word	0x2
	.byte	0x77
	.byte	0x18
	.quad	LCFI19
	.quad	LCFI20
	.word	0x2
	.byte	0x77
	.byte	0x20
	.quad	LCFI20
	.quad	LCFI21
	.word	0x2
	.byte	0x77
	.byte	0x28
	.quad	LCFI21
	.quad	LCFI22
	.word	0x2
	.byte	0x77
	.byte	0x30
	.quad	LCFI22
	.quad	LCFI23
	.word	0x2
	.byte	0x77
	.byte	0x38
	.quad	LCFI23
	.quad	LCFI24
	.word	0x3
	.byte	0x77
	.byte	0x90,0x13
	.quad	LCFI24
	.quad	LCFI25
	.word	0x2
	.byte	0x77
	.byte	0x38
	.quad	LCFI25
	.quad	LCFI26
	.word	0x2
	.byte	0x77
	.byte	0x30
	.quad	LCFI26
	.quad	LCFI27
	.word	0x2
	.byte	0x77
	.byte	0x28
	.quad	LCFI27
	.quad	LCFI28
	.word	0x2
	.byte	0x77
	.byte	0x20
	.quad	LCFI28
	.quad	LCFI29
	.word	0x2
	.byte	0x77
	.byte	0x18
	.quad	LCFI29
	.quad	LCFI30
	.word	0x2
	.byte	0x77
	.byte	0x10
	.quad	LCFI30
	.quad	LCFI31
	.word	0x2
	.byte	0x77
	.byte	0x8
	.quad	LCFI31
	.quad	LFE22
	.word	0x3
	.byte	0x77
	.byte	0x90,0x13
	.quad	0
	.quad	0
LLST20:
	.quad	LVL56
	.quad	LVL57
	.word	0x1
	.byte	0x55
	.quad	0
	.quad	0
LLST21:
	.quad	LVL56
	.quad	LVL58
	.word	0x1
	.byte	0x54
	.quad	LVL58
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0x80,0x6d
	.quad	0
	.quad	0
LLST22:
	.quad	LVL119
	.quad	LVL122-1
	.word	0x1
	.byte	0x50
	.quad	LVL122
	.quad	LVL124
	.word	0x1
	.byte	0x50
	.quad	LVL225
	.quad	LVL226
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST23:
	.quad	LVL109
	.quad	LVL110
	.word	0x1
	.byte	0x51
	.quad	0
	.quad	0
LLST24:
	.quad	LVL68
	.quad	LVL69
	.word	0x1
	.byte	0x50
	.quad	LVL69
	.quad	LVL72
	.word	0x1
	.byte	0x53
	.quad	LVL72
	.quad	LVL74-1
	.word	0x1
	.byte	0x50
	.quad	LVL74-1
	.quad	LVL84
	.word	0x1
	.byte	0x53
	.quad	LVL90
	.quad	LVL92
	.word	0x1
	.byte	0x53
	.quad	LVL154
	.quad	LVL155
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST25:
	.quad	LVL120
	.quad	LVL123
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST26:
	.quad	LVL158
	.quad	LVL159-1
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST27:
	.quad	LVL114
	.quad	LVL152
	.word	0x1
	.byte	0x5f
	.quad	LVL179
	.quad	LVL180
	.word	0x1
	.byte	0x5f
	.quad	LVL184
	.quad	LVL213
	.word	0x1
	.byte	0x5f
	.quad	LVL225
	.quad	LVL226
	.word	0x1
	.byte	0x5f
	.quad	LVL234
	.quad	LVL238
	.word	0x1
	.byte	0x5f
	.quad	LVL240
	.quad	LVL254
	.word	0x1
	.byte	0x5f
	.quad	LVL258
	.quad	LVL259
	.word	0x1
	.byte	0x5f
	.quad	0
	.quad	0
LLST28:
	.quad	LVL216
	.quad	LVL217
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST29:
	.quad	LVL164
	.quad	LVL165
	.word	0x1
	.byte	0x50
	.quad	LVL165
	.quad	LVL166
	.word	0x3
	.byte	0x91
	.byte	0x90,0x6f
	.quad	0
	.quad	0
LLST30:
	.quad	LVL69
	.quad	LVL70-1
	.word	0x1
	.byte	0x50
	.quad	LVL70-1
	.quad	LVL73
	.word	0x1
	.byte	0x5d
	.quad	LVL76
	.quad	LVL77-1
	.word	0x1
	.byte	0x50
	.quad	LVL77-1
	.quad	LVL82
	.word	0x1
	.byte	0x5d
	.quad	LVL90
	.quad	LVL92
	.word	0x1
	.byte	0x5d
	.quad	0
	.quad	0
LLST31:
	.quad	LVL231
	.quad	LVL232-1
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST32:
	.quad	LVL231
	.quad	LVL232-1
	.word	0x2
	.byte	0x70
	.byte	0x30
	.quad	0
	.quad	0
LLST33:
	.quad	LVL85
	.quad	LVL90
	.word	0x3
	.byte	0x91
	.byte	0x94,0x6d
	.quad	LVL92
	.quad	LVL154
	.word	0x3
	.byte	0x91
	.byte	0x94,0x6d
	.quad	LVL155
	.quad	LVL226
	.word	0x3
	.byte	0x91
	.byte	0x94,0x6d
	.quad	LVL229
	.quad	LVL237
	.word	0x3
	.byte	0x91
	.byte	0x94,0x6d
	.quad	LVL237
	.quad	LVL238
	.word	0x1
	.byte	0x50
	.quad	LVL238
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0x94,0x6d
	.quad	0
	.quad	0
LLST34:
	.quad	LVL162
	.quad	LVL163
	.word	0x1
	.byte	0x50
	.quad	LVL271
	.quad	LVL272
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST35:
	.quad	LVL82
	.quad	LVL90
	.word	0x3
	.byte	0x91
	.byte	0x90,0x6d
	.quad	LVL92
	.quad	LVL154
	.word	0x3
	.byte	0x91
	.byte	0x90,0x6d
	.quad	LVL155
	.quad	LVL226
	.word	0x3
	.byte	0x91
	.byte	0x90,0x6d
	.quad	LVL229
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0x90,0x6d
	.quad	0
	.quad	0
LLST36:
	.quad	LVL62
	.quad	LVL63
	.word	0x1
	.byte	0x50
	.quad	LVL63
	.quad	LVL64-1
	.word	0x1
	.byte	0x51
	.quad	LVL64-1
	.quad	LVL68
	.word	0x1
	.byte	0x53
	.quad	LVL226
	.quad	LVL227
	.word	0x1
	.byte	0x50
	.quad	LVL227
	.quad	LVL229
	.word	0x1
	.byte	0x53
	.quad	0
	.quad	0
LLST37:
	.quad	LVL66
	.quad	LVL67-1
	.word	0x1
	.byte	0x50
	.quad	LVL67-1
	.quad	LVL85
	.word	0x1
	.byte	0x56
	.quad	LVL90
	.quad	LVL92
	.word	0x1
	.byte	0x56
	.quad	LVL154
	.quad	LVL155
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST38:
	.quad	LVL78
	.quad	LVL79-1
	.word	0x1
	.byte	0x55
	.quad	LVL79-1
	.quad	LVL82
	.word	0x1
	.byte	0x5d
	.quad	LVL90
	.quad	LVL92
	.word	0x1
	.byte	0x5d
	.quad	0
	.quad	0
LLST39:
	.quad	LVL86
	.quad	LVL90
	.word	0x2
	.byte	0x7c
	.byte	0
	.quad	LVL92
	.quad	LVL153
	.word	0x2
	.byte	0x7c
	.byte	0
	.quad	LVL153
	.quad	LVL154
	.word	0x3
	.byte	0x91
	.byte	0xc4,0x6d
	.quad	LVL155
	.quad	LVL166
	.word	0x2
	.byte	0x7c
	.byte	0
	.quad	LVL166
	.quad	LVL179
	.word	0x3
	.byte	0x91
	.byte	0xc4,0x6d
	.quad	LVL179
	.quad	LVL226
	.word	0x2
	.byte	0x7c
	.byte	0
	.quad	LVL229
	.quad	LVL259
	.word	0x2
	.byte	0x7c
	.byte	0
	.quad	LVL259
	.quad	LVL271
	.word	0x3
	.byte	0x91
	.byte	0xc4,0x6d
	.quad	LVL271
	.quad	LVL273
	.word	0x2
	.byte	0x7c
	.byte	0
	.quad	LVL273
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0xc4,0x6d
	.quad	0
	.quad	0
LLST40:
	.quad	LVL87
	.quad	LVL88
	.word	0x1
	.byte	0x50
	.quad	LVL88
	.quad	LVL89-1
	.word	0x1
	.byte	0x54
	.quad	LVL92
	.quad	LVL93
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST41:
	.quad	LVL97
	.quad	LVL152
	.word	0x3
	.byte	0x77
	.byte	0
	.byte	0x6
	.quad	LVL155
	.quad	LVL226
	.word	0x3
	.byte	0x77
	.byte	0
	.byte	0x6
	.quad	LVL229
	.quad	LFE22
	.word	0x3
	.byte	0x77
	.byte	0
	.byte	0x6
	.quad	0
	.quad	0
LLST42:
	.quad	LVL98
	.quad	LVL99
	.word	0x1
	.byte	0x50
	.quad	LVL99
	.quad	LVL100-1
	.word	0x1
	.byte	0x54
	.quad	LVL101
	.quad	LVL102-1
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST43:
	.quad	LVL102
	.quad	LVL152
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	LVL155
	.quad	LVL226
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	LVL229
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	0
	.quad	0
LLST44:
	.quad	LVL102
	.quad	LVL103
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	LVL103
	.quad	LVL107
	.word	0x1
	.byte	0x51
	.quad	0
	.quad	0
LLST45:
	.quad	LVL102
	.quad	LVL103
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	LVL103
	.quad	LVL108
	.word	0x1
	.byte	0x52
	.quad	0
	.quad	0
LLST46:
	.quad	LVL106
	.quad	LVL152
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	LVL155
	.quad	LVL226
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	LVL229
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	0
	.quad	0
LLST47:
	.quad	LVL117
	.quad	LVL119-1
	.word	0x4
	.byte	0x91
	.byte	0x80,0x6d
	.byte	0x6
	.quad	0
	.quad	0
LLST48:
	.quad	LVL125
	.quad	LVL131
	.word	0x1
	.byte	0x5d
	.quad	0
	.quad	0
LLST49:
	.quad	LVL125
	.quad	LVL126-1
	.word	0x1
	.byte	0x51
	.quad	LVL126-1
	.quad	LVL152
	.word	0x1
	.byte	0x56
	.quad	LVL184
	.quad	LVL190
	.word	0x1
	.byte	0x56
	.quad	LVL240
	.quad	LVL241
	.word	0x1
	.byte	0x56
	.quad	LVL243
	.quad	LVL245
	.word	0x1
	.byte	0x56
	.quad	LVL250
	.quad	LVL254
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST50:
	.quad	LVL133
	.quad	LVL134-1
	.word	0x1
	.byte	0x50
	.quad	LVL134-1
	.quad	LVL152
	.word	0x1
	.byte	0x5e
	.quad	LVL179
	.quad	LVL182
	.word	0x1
	.byte	0x5e
	.quad	LVL184
	.quad	LVL225
	.word	0x1
	.byte	0x5e
	.quad	LVL243
	.quad	LVL245
	.word	0x1
	.byte	0x5e
	.quad	LVL247
	.quad	LVL259
	.word	0x1
	.byte	0x5e
	.quad	0
	.quad	0
LLST51:
	.quad	LVL135
	.quad	LVL138
	.word	0x1
	.byte	0x50
	.quad	LVL138
	.quad	LVL152
	.word	0x1
	.byte	0x5d
	.quad	LVL184
	.quad	LVL207
	.word	0x1
	.byte	0x5d
	.quad	LVL243
	.quad	LVL244
	.word	0x1
	.byte	0x50
	.quad	LVL244
	.quad	LVL245
	.word	0x1
	.byte	0x5d
	.quad	LVL247
	.quad	LVL254
	.word	0x1
	.byte	0x5d
	.quad	LVL258
	.quad	LVL259
	.word	0x1
	.byte	0x5d
	.quad	0
	.quad	0
LLST52:
	.quad	LVL146
	.quad	LVL150
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	LVL151
	.quad	LVL152
	.word	0x1
	.byte	0x50
	.quad	LVL186
	.quad	LVL188
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	LVL251
	.quad	LVL252
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	LVL253
	.quad	LVL254
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	0
	.quad	0
LLST55:
	.quad	LVL126
	.quad	LVL127
	.word	0x1
	.byte	0x5e
	.quad	0
	.quad	0
LLST56:
	.quad	LVL137
	.quad	LVL139
	.word	0x1
	.byte	0x51
	.quad	LVL140
	.quad	LVL143
	.word	0x1
	.byte	0x51
	.quad	LVL147
	.quad	LVL148
	.word	0x1
	.byte	0x51
	.quad	LVL185
	.quad	LVL187
	.word	0x1
	.byte	0x51
	.quad	LVL250
	.quad	LVL251
	.word	0x1
	.byte	0x51
	.quad	0
	.quad	0
LLST57:
	.quad	LVL179
	.quad	LVL182
	.word	0x1
	.byte	0x5e
	.quad	LVL189
	.quad	LVL225
	.word	0x1
	.byte	0x5e
	.quad	LVL247
	.quad	LVL250
	.word	0x1
	.byte	0x5e
	.quad	LVL254
	.quad	LVL259
	.word	0x1
	.byte	0x5e
	.quad	0
	.quad	0
LLST58:
	.quad	LVL179
	.quad	LVL182
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	LVL189
	.quad	LVL225
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	LVL247
	.quad	LVL250
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	LVL254
	.quad	LVL259
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	0
	.quad	0
LLST59:
	.quad	LVL192
	.quad	LVL197
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST60:
	.quad	LVL194
	.quad	LVL199
	.word	0x1
	.byte	0x53
	.quad	0
	.quad	0
LLST61:
	.quad	LVL179
	.quad	LVL182
	.word	0x1
	.byte	0x5e
	.quad	LVL201
	.quad	LVL225
	.word	0x1
	.byte	0x5e
	.quad	LVL247
	.quad	LVL250
	.word	0x1
	.byte	0x5e
	.quad	LVL254
	.quad	LVL259
	.word	0x1
	.byte	0x5e
	.quad	0
	.quad	0
LLST62:
	.quad	LVL179
	.quad	LVL182
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	LVL201
	.quad	LVL225
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	LVL247
	.quad	LVL250
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	LVL254
	.quad	LVL259
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	0
	.quad	0
LLST63:
	.quad	LVL202
	.quad	LVL203
	.word	0x1
	.byte	0x50
	.quad	LVL247
	.quad	LVL248
	.word	0x1
	.byte	0x50
	.quad	LVL258
	.quad	LVL259-1
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST64:
	.quad	LVL166
	.quad	LVL179
	.word	0x3
	.byte	0x91
	.byte	0x98,0x6d
	.quad	LVL259
	.quad	LVL271
	.word	0x3
	.byte	0x91
	.byte	0x98,0x6d
	.quad	LVL273
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0x98,0x6d
	.quad	0
	.quad	0
LLST65:
	.quad	LVL166
	.quad	LVL171
	.word	0x1
	.byte	0x53
	.quad	LVL262
	.quad	LVL263
	.word	0x1
	.byte	0x53
	.quad	LVL265
	.quad	LVL267
	.word	0x1
	.byte	0x53
	.quad	LVL274
	.quad	LVL275
	.word	0x1
	.byte	0x53
	.quad	LVL276
	.quad	LFE22
	.word	0x1
	.byte	0x53
	.quad	0
	.quad	0
LLST66:
	.quad	LVL166
	.quad	LVL175
	.word	0x1
	.byte	0x56
	.quad	LVL259
	.quad	LVL271
	.word	0x1
	.byte	0x56
	.quad	LVL273
	.quad	LFE22
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST67:
	.quad	LVL168
	.quad	LVL179
	.word	0x1
	.byte	0x5c
	.quad	LVL259
	.quad	LVL271
	.word	0x1
	.byte	0x5c
	.quad	LVL273
	.quad	LVL274
	.word	0x1
	.byte	0x5c
	.quad	LVL275
	.quad	LFE22
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST68:
	.quad	LVL168
	.quad	LVL175
	.word	0x1
	.byte	0x56
	.quad	LVL259
	.quad	LVL265
	.word	0x1
	.byte	0x56
	.quad	LVL273
	.quad	LVL274
	.word	0x1
	.byte	0x56
	.quad	LVL275
	.quad	LVL276
	.word	0x1
	.byte	0x56
	.quad	LVL277
	.quad	LFE22
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST69:
	.quad	LVL169
	.quad	LVL172
	.word	0x1
	.byte	0x50
	.quad	LVL259
	.quad	LVL260-1
	.word	0x1
	.byte	0x50
	.quad	LVL262
	.quad	LVL264-1
	.word	0x1
	.byte	0x50
	.quad	LVL277
	.quad	LVL278
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST70:
	.quad	LVL179
	.quad	LVL182
	.word	0x1
	.byte	0x56
	.quad	LVL208
	.quad	LVL209
	.word	0x1
	.byte	0x50
	.quad	LVL209
	.quad	LVL220
	.word	0x1
	.byte	0x56
	.quad	LVL254
	.quad	LVL258
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST71:
	.quad	LVL179
	.quad	LVL180
	.word	0x1
	.byte	0x50
	.quad	LVL209
	.quad	LVL210
	.word	0x1
	.byte	0x50
	.quad	LVL210
	.quad	LVL211-1
	.word	0x1
	.byte	0x52
	.quad	LVL212
	.quad	LVL214-1
	.word	0x1
	.byte	0x50
	.quad	LVL254
	.quad	LVL255-1
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST72:
	.quad	LVL221
	.quad	LVL225
	.word	0x2
	.byte	0x76
	.byte	0
	.quad	0
	.quad	0
LLST73:
	.quad	LVL222
	.quad	LVL223
	.word	0x1
	.byte	0x50
	.quad	LVL223
	.quad	LVL224-1
	.word	0x1
	.byte	0x54
	.quad	0
	.quad	0
	.section __DWARF,__debug_pubnames,regular,debug
Lsection__debug_pubnames:
	.long	0x187
	.word	0x2
	.set L$set$193,Ldebug_info0-Lsection__debug_info
	.long L$set$193
	.long	0x1b58
	.long	0xb93
	.ascii "__sigbits\0"
	.long	0xbbb
	.ascii "file_exist\0"
	.long	0xbf5
	.ascii "RemoveSpaces\0"
	.long	0xc30
	.ascii "err_setarg0\0"
	.long	0xc53
	.ascii "err_syswarn\0"
	.long	0xc80
	.ascii "dump_argv\0"
	.long	0xcd5
	.ascii "StartsWith\0"
	.long	0xd00
	.ascii "fork_pipes\0"
	.long	0xd52
	.ascii "Janitor\0"
	.long	0xd8f
	.ascii "sighandler\0"
	.long	0xdfc
	.ascii "err_syserr\0"
	.long	0xe53
	.ascii "err_vsyswarn\0"
	.long	0xe94
	.ascii "err_sysexit\0"
	.long	0xf1d
	.ascii "exec_pipe_command\0"
	.long	0xf81
	.ascii "exec_nth_command\0"
	.long	0x10e2
	.ascii "spawn_proc\0"
	.long	0x1126
	.ascii "corpse_collector\0"
	.long	0x1168
	.ascii "exec_arguments\0"
	.long	0x11e0
	.ascii "exec_pipeline\0"
	.long	0x1235
	.ascii "dump_pipeline\0"
	.long	0x127d
	.ascii "main\0"
	.long	0x1acb
	.ascii "arg0\0"
	.long	0x1b1f
	.ascii "isSignal\0"
	.long	0x1b3a
	.ascii "foreground\0"
	.long	0
	.section __DWARF,__debug_pubtypes,regular,debug
Lsection__debug_pubtypes:
	.long	0x37e
	.word	0x2
	.set L$set$194,Ldebug_info0-Lsection__debug_info
	.long L$set$194
	.long	0x1b58
	.long	0xaf
	.ascii "signed char\0"
	.long	0xbe
	.ascii "unsigned char\0"
	.long	0xcf
	.ascii "short int\0"
	.long	0xee
	.ascii "short unsigned int\0"
	.long	0xdc
	.ascii "__uint16_t\0"
	.long	0x115
	.ascii "int\0"
	.long	0x104
	.ascii "__int32_t\0"
	.long	0x12e
	.ascii "unsigned int\0"
	.long	0x11c
	.ascii "__uint32_t\0"
	.long	0x14f
	.ascii "long long int\0"
	.long	0x13e
	.ascii "__int64_t\0"
	.long	0x172
	.ascii "long long unsigned int\0"
	.long	0x160
	.ascii "__uint64_t\0"
	.long	0x18c
	.ascii "long int\0"
	.long	0x198
	.ascii "sizetype\0"
	.long	0x1a4
	.ascii "char\0"
	.long	0x1c3
	.ascii "long unsigned int\0"
	.long	0x1ac
	.ascii "__darwin_size_t\0"
	.long	0x200
	.ascii "__va_list_tag\0"
	.long	0x1d8
	.ascii "__darwin_va_list\0"
	.long	0x275
	.ascii "__darwin_time_t\0"
	.long	0x28c
	.ascii "__darwin_blkcnt_t\0"
	.long	0x2a5
	.ascii "__darwin_blksize_t\0"
	.long	0x2bf
	.ascii "__darwin_dev_t\0"
	.long	0x2d5
	.ascii "__darwin_gid_t\0"
	.long	0x2eb
	.ascii "__darwin_ino64_t\0"
	.long	0x303
	.ascii "__darwin_mode_t\0"
	.long	0x31a
	.ascii "__darwin_off_t\0"
	.long	0x330
	.ascii "__darwin_pid_t\0"
	.long	0x346
	.ascii "__darwin_sigset_t\0"
	.long	0x35f
	.ascii "__darwin_suseconds_t\0"
	.long	0x37b
	.ascii "__darwin_uid_t\0"
	.long	0x391
	.ascii "gid_t\0"
	.long	0x39e
	.ascii "size_t\0"
	.long	0x3ac
	.ascii "uid_t\0"
	.long	0x3b9
	.ascii "passwd\0"
	.long	0x4a9
	.ascii "pid_t\0"
	.long	0x4b6
	.ascii "sigset_t\0"
	.long	0x4c6
	.ascii "sigval\0"
	.long	0x4f8
	.ascii "__siginfo\0"
	.long	0x5d0
	.ascii "siginfo_t\0"
	.long	0x5e1
	.ascii "__sigaction_u\0"
	.long	0x655
	.ascii "sigaction\0"
	.long	0x69f
	.ascii "fpos_t\0"
	.long	0x6ad
	.ascii "__sbuf\0"
	.long	0x6e3
	.ascii "__sFILE\0"
	.long	0x8e5
	.ascii "FILE\0"
	.long	0x8f1
	.ascii "timeval\0"
	.long	0x925
	.ascii "blkcnt_t\0"
	.long	0x935
	.ascii "blksize_t\0"
	.long	0x946
	.ascii "dev_t\0"
	.long	0x953
	.ascii "mode_t\0"
	.long	0x961
	.ascii "nlink_t\0"
	.long	0x970
	.ascii "off_t\0"
	.long	0x97d
	.ascii "time_t\0"
	.long	0x98b
	.ascii "stat\0"
	.long	0xb5c
	.ascii "Pipe\0"
	.long	0xb68
	.ascii "command\0"
	.long	0
	.section __DWARF,__debug_aranges,regular,debug
Lsection__debug_aranges:
	.long	0x4c
	.word	0x2
	.set L$set$195,Ldebug_info0-Lsection__debug_info
	.long L$set$195
	.byte	0x8
	.byte	0
	.word	0
	.word	0
	.quad	Ltext0
	.set L$set$196,Letext0-Ltext0
	.quad L$set$196
	.quad	Ltext_cold0
	.set L$set$197,Letext_cold0-Ltext_cold0
	.quad L$set$197
	.quad	LFB22
	.set L$set$198,LFE22-LFB22
	.quad L$set$198
	.quad	0
	.quad	0
	.section __DWARF,__debug_line,regular,debug
Lsection__debug_line:
Ldebug_line0:
	.set L$set$199,LELT0-LSLT0
	.long L$set$199
LSLT0:
	.word	0x2
	.set L$set$200,LELTP0-LASLTP0
	.long L$set$200
LASLTP0:
	.byte	0x1
	.byte	0x1
	.byte	0xf6
	.byte	0xf2
	.byte	0xd
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x1
	.ascii "/usr/include"
	.byte	0
	.ascii "/usr/include/i386"
	.byte	0
	.ascii "/usr/include/sys"
	.byte	0
	.ascii "/usr/include/sys/_types"
	.byte	0
	.byte	0
	.ascii "c_posix.c\0"
	.byte	0
	.byte	0
	.byte	0
	.ascii "i386/_types.h\0"
	.byte	0x1
	.byte	0
	.byte	0
	.ascii "<built-in>\0"
	.byte	0
	.byte	0
	.byte	0
	.ascii "_types.h\0"
	.byte	0x3
	.byte	0
	.byte	0
	.ascii "_gid_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_size_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_uid_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "pwd.h\0"
	.byte	0x1
	.byte	0
	.byte	0
	.ascii "_pid_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_sigset_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "signal.h\0"
	.byte	0x3
	.byte	0
	.byte	0
	.ascii "stdio.h\0"
	.byte	0x1
	.byte	0
	.byte	0
	.ascii "_timeval.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_blkcnt_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_blksize_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_dev_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_mode_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_nlink_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_off_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "_time_t.h\0"
	.byte	0x4
	.byte	0
	.byte	0
	.ascii "stat.h\0"
	.byte	0x3
	.byte	0
	.byte	0
	.ascii "signal.h\0"
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0
LELTP0:
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM50
	.byte	0x3
	.byte	0xed,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM51
	.byte	0x26
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM52
	.byte	0x38
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM53
	.byte	0x3
	.byte	0x50
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM54
	.byte	0x26
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM55
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM56
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM57
	.byte	0x3
	.byte	0x6f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM58
	.byte	0x47
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM59
	.byte	0x3
	.byte	0x61
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM60
	.byte	0x31
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM61
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM62
	.byte	0x14
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM63
	.byte	0x3
	.byte	0x64
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM64
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM65
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM66
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM67
	.byte	0x31
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM68
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM69
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM70
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM71
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM72
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM73
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM74
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM75
	.byte	0x3
	.byte	0xb9,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM76
	.byte	0x61
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM77
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM78
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM79
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM80
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM81
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM82
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM83
	.byte	0x2c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM84
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM85
	.byte	0x3
	.byte	0x69
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM86
	.byte	0x2e
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM87
	.byte	0x3
	.byte	0x69
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM88
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM89
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM90
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM91
	.byte	0x3
	.byte	0xad,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM92
	.byte	0x6a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM93
	.byte	0x3
	.byte	0xad,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM94
	.byte	0x6b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM95
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM96
	.byte	0x14
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM97
	.byte	0x26
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM98
	.byte	0x26
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM99
	.byte	0x3
	.byte	0x45
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM100
	.byte	0x52
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM101
	.byte	0xcd
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM102
	.byte	0x3
	.byte	0xa8,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM103
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM104
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM105
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM106
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM107
	.byte	0x91
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM108
	.byte	0x2b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM109
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM110
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM111
	.byte	0x3
	.byte	0xe3,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM112
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM113
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM114
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM115
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM116
	.byte	0xac
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM117
	.byte	0x3
	.byte	0xfc,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM118
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM119
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM120
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM121
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM122
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM123
	.byte	0x13
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM124
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM125
	.byte	0x3
	.byte	0x91,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM126
	.byte	0x3
	.byte	0xf2,0x1
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM127
	.byte	0x3
	.byte	0x8e,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM128
	.byte	0x3
	.byte	0xf2,0x1
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM129
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM130
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM131
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM132
	.byte	0x3
	.byte	0x89,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM133
	.byte	0x3
	.byte	0xd9,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM134
	.byte	0x1f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM135
	.byte	0x23
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM136
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM137
	.byte	0x20
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM138
	.byte	0x3
	.byte	0xd3,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM139
	.byte	0x3
	.byte	0xb2,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM140
	.byte	0x3
	.byte	0xce,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM141
	.byte	0x3
	.byte	0xb2,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM142
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM143
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM144
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM145
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM146
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM147
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM148
	.byte	0x14
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM149
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM150
	.byte	0x3
	.byte	0x84,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM151
	.byte	0x3
	.byte	0xfc,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM152
	.byte	0x3
	.byte	0x84,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM153
	.byte	0x3
	.byte	0xfc,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM154
	.byte	0x3
	.byte	0x84,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM155
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM156
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM157
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM158
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM159
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM160
	.byte	0x2f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM161
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM162
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM163
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM164
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM165
	.byte	0x11
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM166
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM167
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM168
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM169
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM170
	.byte	0x13
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM171
	.byte	0x23
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM172
	.byte	0x3
	.byte	0x74
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM173
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM174
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM175
	.byte	0x21
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM176
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM177
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM178
	.byte	0x3
	.byte	0x72
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM179
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM180
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM181
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM182
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM183
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM184
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM185
	.byte	0x3
	.byte	0x8a,0x4
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM186
	.byte	0x3
	.byte	0x89,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM187
	.byte	0x48
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM188
	.byte	0x23
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM189
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM190
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM191
	.byte	0x3
	.byte	0xf2,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM192
	.byte	0x3
	.byte	0x9e,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM193
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM194
	.byte	0x24
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM195
	.byte	0x27
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM196
	.byte	0x3
	.byte	0xea,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM197
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM198
	.byte	0x3
	.byte	0x93,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM199
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM200
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM201
	.byte	0xf
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM202
	.byte	0x23
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM203
	.byte	0x12
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM204
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM205
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM206
	.byte	0x12
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM207
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM208
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM209
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM210
	.byte	0x12
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM211
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM212
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM213
	.byte	0x3
	.byte	0xe2,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM214
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM215
	.byte	0x3
	.byte	0x59
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM216
	.byte	0x3e
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM217
	.byte	0x3
	.byte	0x5b
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM218
	.byte	0x3c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM219
	.byte	0x3
	.byte	0x5b
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM220
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM221
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM222
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM223
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM224
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM225
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM226
	.byte	0x3
	.byte	0x87,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM227
	.byte	0x32
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM228
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM229
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM230
	.byte	0x3
	.byte	0xf3,0x7b
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM231
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM232
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM233
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM234
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM235
	.byte	0x3
	.byte	0x54
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM236
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM237
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM238
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM239
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM240
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM241
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM242
	.byte	0x11
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM243
	.byte	0x1f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM244
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM245
	.byte	0x3
	.byte	0x53
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM246
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM247
	.byte	0x68
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM248
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM249
	.byte	0x3
	.byte	0xb6,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM250
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM251
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM252
	.byte	0x3
	.byte	0x90,0x4
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM253
	.byte	0x1f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM254
	.byte	0x24
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM255
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM256
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM257
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM258
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM259
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM260
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM261
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM262
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM263
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM264
	.byte	0x3
	.byte	0x9e,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM265
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM266
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM267
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM268
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM269
	.byte	0x3
	.byte	0xa5,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM270
	.byte	0x3
	.byte	0xbe,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM271
	.byte	0x5e
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM272
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM273
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM274
	.byte	0x75
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM275
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM276
	.byte	0x3
	.byte	0xa7,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM277
	.byte	0x3
	.byte	0xfe,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM278
	.byte	0x3
	.byte	0xe6,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM279
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM280
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM281
	.byte	0x3
	.byte	0xb7,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM282
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM283
	.byte	0x3
	.byte	0xbd,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM284
	.byte	0x3
	.byte	0x8b,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM285
	.byte	0x53
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM286
	.byte	0x28
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM287
	.byte	0xf
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM288
	.byte	0x3
	.byte	0xe1,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM289
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM290
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM291
	.byte	0x3
	.byte	0xdb,0x7b
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM292
	.byte	0xb0
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM293
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM294
	.byte	0x23
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM295
	.byte	0x2d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM296
	.byte	0xf
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM297
	.byte	0x1f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM298
	.byte	0xf
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM299
	.byte	0x20
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM300
	.byte	0xe
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM301
	.byte	0x22
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM302
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM303
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM304
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM305
	.byte	0x3
	.byte	0xe9,0x1
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM306
	.byte	0x3
	.byte	0xf1,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM307
	.byte	0x30
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM308
	.byte	0x3
	.byte	0x61
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM309
	.byte	0x3f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM310
	.byte	0x3
	.byte	0x67
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LHOTE55
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM3
	.byte	0xf2
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM4
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM5
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM6
	.byte	0x14
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM7
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM8
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM9
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM10
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM11
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM12
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM13
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	Letext_cold0
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM1
	.byte	0x3
	.byte	0xe6,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM2
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM14
	.byte	0x3
	.byte	0xe2,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM15
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM16
	.byte	0x3
	.byte	0x6d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM17
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM18
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM19
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM20
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM21
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM22
	.byte	0x28
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM23
	.byte	0x3
	.byte	0xe0,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM24
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM25
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM26
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM27
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM28
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM29
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM30
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM31
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM32
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM33
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM34
	.byte	0x3
	.byte	0x72
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM35
	.byte	0x11
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM36
	.byte	0x34
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM37
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM38
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM39
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM40
	.byte	0x3
	.byte	0x68
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM41
	.byte	0xa0
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM42
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM43
	.byte	0x3
	.byte	0x75
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM44
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM45
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM46
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM47
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM48
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM49
	.byte	0x20
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	Letext0
	.byte	0
	.byte	0x1
	.byte	0x1
LELT0:
	.section __DWARF,__debug_str,regular,debug
Lsection__debug_str:
LASF6:
	.ascii "exec_pipeline\0"
LASF5:
	.ascii "exec_pipe_command\0"
LASF4:
	.ascii "status\0"
LASF0:
	.ascii "__sigaction_u\0"
LASF3:
	.ascii "__func__\0"
LASF2:
	.ascii "dump_argv\0"
LASF1:
	.ascii "args\0"
	.subsections_via_symbols
