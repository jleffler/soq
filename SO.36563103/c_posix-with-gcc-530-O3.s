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
	.ascii "Processing %d [%s]\12\0"
LC44:
	.ascii "|\0"
	.align 3
LC45:
	.ascii "Syntax error: pipe before any command\0"
	.align 3
LC46:
	.ascii "Syntax error: two pipes with no command between\0"
	.align 3
LC47:
	.ascii "Syntax error: pipe with no command following\0"
LC48:
	.ascii "SOC\0"
LC49:
	.ascii "cmd [%d]\0"
LC50:
	.ascii "EOC\0"
LC51:
	.ascii "%d: child %d status 0x%.4X\12\0"
LC52:
	.ascii "Execution time %ld.%03ld ms\12\0"
LC53:
	.ascii "PAGER\0"
LC54:
	.ascii "miniShell>> \0"
LC55:
	.ascii "unixinfo\0"
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDB56:
	.section __TEXT,__text_startup,regular,pure_instructions
LHOTB56:
	.align 4
	.globl _main
_main:
LFB22:
LM50:
LVL55:
	pushq	%r15
LCFI17:
LM51:
	leaq	LC15(%rip), %rax
LM52:
	movl	$2, %edi
LVL56:
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
	subq	$2408, %rsp
LCFI23:
LM54:
	movq	%rax, 144(%rsp)
LM55:
	leaq	LC16(%rip), %rax
	movq	%rax, 160(%rsp)
LM56:
	leaq	LC17(%rip), %rax
LM57:
	movq	%rsi, 16(%rsp)
LM58:
	leaq	240(%rsp), %rdx
LM59:
	movq	%rax, 176(%rsp)
LM60:
	leaq	224(%rsp), %rsi
LVL57:
LM61:
	leaq	_sighandler(%rip), %rax
LM62:
	movq	$0, 232(%rsp)
LM63:
	movq	$0, 152(%rsp)
LM64:
	movq	$0, 168(%rsp)
LM65:
	movq	$0, 184(%rsp)
LM66:
	movl	$0, 92(%rsp)
LVL58:
LM67:
	movq	%rax, 224(%rsp)
LM68:
	movl	$64, 236(%rsp)
LM69:
	call	_sigaction
LVL59:
LM70:
	leaq	LC18(%rip), %rdi
	call	_getenv
LVL60:
LM71:
	testq	%rax, %rax
LM72:
	movq	%rax, %rbx
LVL61:
LM73:
	je	L188
LM74:
	leaq	LC18(%rip), %rsi
	movq	%rax, %rdx
	xorl	%eax, %eax
LVL62:
	leaq	LC20(%rip), %rdi
	call	_printf
LVL63:
L41:
LBB77:
LBB78:
LM75:
	leaq	1376(%rsp), %r12
LBE78:
LBE77:
LM76:
	movq	%rbx, %rdi
	call	_strdup
LVL64:
LM77:
	leaq	LC21(%rip), %rsi
	movq	%rax, %rdi
LM78:
	movq	%rax, %rbp
LVL65:
LM79:
	call	_strtok
LVL66:
LM80:
	testq	%rax, %rax
LM81:
	movq	%rax, %rbx
LVL67:
LM82:
	jne	L150
	jmp	L50
LVL68:
	.align 4
L44:
LM83:
	leaq	LC22(%rip), %rdi
	call	_puts
LVL69:
L106:
LM84:
	leaq	LC21(%rip), %rsi
	xorl	%edi, %edi
	call	_strtok
LVL70:
LM85:
	testq	%rax, %rax
LM86:
	movq	%rax, %rbx
LVL71:
LM87:
	je	L50
LVL72:
L150:
LM88:
	movq	%rbx, %rdi
	call	_strlen
LVL73:
	leaq	6(%rax), %rdi
	call	_malloc
LVL74:
	testq	%rax, %rax
	movq	%rax, %r13
LVL75:
	je	L44
LM89:
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_strcpy
LVL76:
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
LBB82:
LBB79:
LM91:
	movq	%r13, %rdi
LBE79:
LBE82:
LM92:
	shrl	$16, %ecx
	testl	$32896, %eax
	cmove	%ecx, %eax
	leaq	2(%rdx), %rcx
	movl	%eax, %esi
	cmove	%rcx, %rdx
	addb	%al, %sil
	movl	$115, %eax
LBB83:
LBB80:
LM93:
	movq	%r12, %rsi
LBE80:
LBE83:
LM94:
	sbbq	$3, %rdx
	movl	$1936026671, (%rdx)
	movw	%ax, 4(%rdx)
LVL77:
LBB84:
LBB81:
LM95:
	call	_stat$INODE64
LVL78:
LBE81:
LBE84:
LM96:
	testl	%eax, %eax
	jne	L189
LVL79:
LM97:
	movq	%r13, %rdi
	call	_free
LVL80:
LM98:
	movl	$0, 32(%rsp)
LVL81:
L43:
	leaq	100(%rsp), %r15
LM99:
	movq	%rbp, %rdi
	call	_free
LVL82:
	leaq	104(%rsp), %rax
LM100:
	movl	$0, 36(%rsp)
	movq	%rax, (%rsp)
LM101:
	leaq	1376(%rsp), %rax
	movq	%rax, 8(%rsp)
	leaq	320(%rsp), %rax
	movq	%rax, 40(%rsp)
LM102:
	leaq	92(%rsp), %rax
	leaq	352(%rsp), %rbx
LVL83:
	movq	%rax, 48(%rsp)
LVL84:
L57:
	movl	$20, 100(%rsp)
LVL85:
L117:
LBB85:
LBB86:
LBB87:
LM103:
	movl	$1, %edx
	movq	%r15, %rsi
	movl	$-1, %edi
	call	_waitpid
LVL86:
LM104:
	testl	%eax, %eax
	jle	L51
LM105:
	cmpl	_foreground(%rip), %eax
	je	L117
LM106:
	movl	100(%rsp), %edx
	andl	$127, %edx
	cmpl	$127, %edx
	je	L117
LM107:
	leaq	LC23(%rip), %rdi
	movl	%eax, %esi
	xorl	%eax, %eax
LVL87:
	call	_printf
LVL88:
	jmp	L117
LVL89:
L189:
LBE87:
LBE86:
LBE85:
LM108:
	movq	%r13, %rdi
	call	_free
LVL90:
	jmp	L106
LVL91:
	.align 4
L51:
LM109:
	leaq	LC54(%rip), %rdi
	xorl	%eax, %eax
	call	_printf
LVL92:
LM110:
	xorl	%esi, %esi
	movl	$1024, %edx
	movq	%rbx, %rdi
	call	_memset
LVL93:
LM111:
	movq	___stdinp@GOTPCREL(%rip), %rax
	movl	$1024, %esi
	movq	%rbx, %rdi
	movq	(%rax), %rdx
	call	_fgets
LVL94:
	testq	%rax, %rax
	je	L138
	movl	$20, 104(%rsp)
LVL95:
L119:
LBB88:
LBB89:
LBB90:
LM112:
	movq	(%rsp), %rsi
	movl	$1, %edx
	movl	$-1, %edi
	call	_waitpid
LVL96:
LM113:
	testl	%eax, %eax
	jle	L53
LM114:
	cmpl	_foreground(%rip), %eax
	je	L119
LM115:
	movl	104(%rsp), %edx
	andl	$127, %edx
	cmpl	$127, %edx
	je	L119
LM116:
	leaq	LC23(%rip), %rdi
	movl	%eax, %esi
	xorl	%eax, %eax
LVL97:
	call	_printf
LVL98:
	jmp	L119
LVL99:
	.align 4
L53:
LBE90:
LBE89:
LBE88:
LM117:
	movq	8(%rsp), %r14
	movl	$1024, %edx
	movq	%rbx, %rsi
	movq	%r14, %rdi
	call	_strncpy
LVL100:
LBB91:
LBB92:
LM118:
	movq	%r14, %rcx
LM119:
	movq	%r14, %rdx
	jmp	L118
LVL101:
	.align 4
L56:
LM120:
	addq	$1, %rcx
LVL102:
LM121:
	cmpb	$32, %al
LM122:
	movb	%al, (%rdx)
LM123:
	setne	%al
	movzbl	%al, %eax
	addq	%rax, %rdx
LVL103:
L118:
LM124:
	movzbl	(%rcx), %eax
	testb	%al, %al
	jne	L56
LM125:
	movb	$0, (%rdx)
LVL104:
LBE92:
LBE91:
LBB93:
LBB94:
LM126:
	cmpb	$10, 1376(%rsp)
LBE94:
LBE93:
LM127:
	movq	%rbx, %rdx
LVL105:
LBB96:
LBB95:
LM128:
	je	L57
LVL106:
L107:
LBE95:
LBE96:
LM129:
	movl	(%rdx), %ecx
	addq	$4, %rdx
	leal	-16843009(%rcx), %eax
	notl	%ecx
	andl	%ecx, %eax
	andl	$-2139062144, %eax
	je	L107
	movl	%eax, %ecx
	shrl	$16, %ecx
	testl	$32896, %eax
	cmove	%ecx, %eax
	leaq	2(%rdx), %rcx
	movl	%eax, %esi
	cmove	%rcx, %rdx
	addb	%al, %sil
	sbbq	$3, %rdx
	subq	%rbx, %rdx
LVL107:
LM130:
	subq	$1, %rdx
LVL108:
	cmpb	$10, 352(%rsp,%rdx)
	jne	L110
LM131:
	movb	$0, 352(%rsp,%rdx)
L110:
LM132:
	leaq	LC24(%rip), %rdi
	movl	$5, %ecx
	movq	%rbx, %rsi
	repz cmpsb
	je	L138
LVL109:
LBB97:
LBB98:
LM133:
	leaq	LC25(%rip), %rdi
	movl	$2, %ecx
	movq	%rbx, %rsi
	repz cmpsb
	je	L190
LVL110:
LBE98:
LBE97:
LBB99:
LBB100:
	leaq	LC55(%rip), %rdi
	movl	$8, %ecx
	movq	%rbx, %rsi
	repz cmpsb
	je	L120
	movq	%rbx, %rax
	xorl	%r14d, %r14d
	movl	$1, %edx
LVL111:
	leaq	80(%rbx), %rcx
	.align 4
L75:
	cmpb	$38, (%rax)
	cmove	%edx, %r14d
LVL112:
	addq	$1, %rax
LVL113:
LBE100:
LBE99:
LM134:
	cmpq	%rcx, %rax
	jne	L75
LM135:
	cmpl	$1, %r14d
	je	L191
LM136:
	leaq	192(%rsp), %rdi
	xorl	%esi, %esi
	call	_gettimeofday
LVL114:
LM137:
	cmpl	$1, _isSignal(%rip)
	je	L192
L79:
LM138:
	movl	36(%rsp), %eax
	movl	%eax, _foreground(%rip)
L78:
LVL115:
LBB102:
LBB103:
LM139:
	movq	16(%rsp), %rax
LBE103:
LBE102:
LM140:
	leaq	LC27(%rip), %rsi
	movq	%rbx, %rdi
LBB105:
LBB104:
LM141:
	movq	(%rax), %rax
	movq	%rax, _arg0(%rip)
LVL116:
LBE104:
LBE105:
LM142:
	call	_strtok
LVL117:
LM143:
	movq	$0, 256(%rsp)
LM144:
	testq	%rax, %rax
	je	L123
	leaq	256(%rsp), %r12
	movl	$1, %ebp
	movq	%r12, %r13
LVL118:
L81:
LM145:
	movq	%rax, 8(%r13)
LM146:
	xorl	%edi, %edi
LM147:
	addl	$1, %ebp
LVL119:
	addq	$8, %r13
LM148:
	leaq	LC27(%rip), %rsi
	call	_strtok
LVL120:
LM149:
	testq	%rax, %rax
	jne	L81
LVL121:
L80:
LM150:
	movslq	%ebp, %rax
LVL122:
LBB106:
LBB107:
LBB108:
LBB109:
LM151:
	movl	%ebp, %edx
	xorl	%r13d, %r13d
LBE109:
LBE108:
LBE107:
LBE106:
LM152:
	movq	%rax, 24(%rsp)
LBB147:
LBB138:
LBB114:
LBB111:
LM153:
	leaq	LC39(%rip), %rsi
LBE111:
LBE114:
LBE138:
LBE147:
LM154:
	movq	$0, 256(%rsp,%rax,8)
LVL123:
LBB148:
LBB139:
LBB115:
LBB112:
LM155:
	leaq	LC40(%rip), %rdi
	xorl	%eax, %eax
	call	_printf
LVL124:
	.align 4
L83:
LBB110:
LM156:
	movq	(%r12,%r13,8), %rsi
	leaq	LC14(%rip), %rax
	leaq	LC41(%rip), %rdi
	testq	%rsi, %rsi
	cmove	%rax, %rsi
	xorl	%eax, %eax
	addq	$1, %r13
LVL125:
	call	_printf
LVL126:
LM157:
	cmpl	%r13d, %ebp
	jg	L83
LBE110:
LM158:
	movl	$10, %edi
	call	_putchar
LVL127:
LM159:
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	call	_fflush
LVL128:
LM160:
	movq	24(%rsp), %r13
	salq	$3, %r13
	cmpq	$0, 256(%rsp,%r13)
	jne	L193
LVL129:
LBE112:
LBE115:
LM161:
	movl	%ebp, %edi
	sarl	%edi
	movslq	%edi, %rdi
	salq	$3, %rdi
	call	_malloc
LVL130:
LM162:
	leaq	8(%r13), %rdi
LM163:
	movq	%rax, 24(%rsp)
LVL131:
LM164:
	call	_malloc
LVL132:
LM165:
	movq	24(%rsp), %rsi
LBB116:
LM166:
	cmpl	$1, %ebp
LBE116:
LM167:
	movq	%rax, 56(%rsp)
LVL133:
LM168:
	movq	%rax, (%rsi)
LVL134:
LBB121:
LM169:
	je	L124
	movq	%r12, %r13
	addq	$8, %rax
LVL135:
	movl	$1, %r12d
LVL136:
	movl	%r14d, 68(%rsp)
	movl	$1, 64(%rsp)
	movq	%r13, %r14
LVL137:
	movl	%r12d, %r13d
LVL138:
	movl	%ebp, %r12d
	movq	%rbx, 72(%rsp)
	movq	%rax, %rbp
LVL139:
L89:
LBB117:
LM170:
	movq	8(%r14), %rbx
LVL140:
LM171:
	leaq	LC43(%rip), %rdi
	movl	%r13d, %esi
	xorl	%eax, %eax
	movq	%rbx, %rdx
	call	_printf
LVL141:
LM172:
	movl	$2, %ecx
	movq	%rbx, %rsi
	leaq	LC44(%rip), %rdi
	repz cmpsb
LVL142:
	jne	L86
LM173:
	cmpl	$1, %r13d
	jne	L87
LM174:
	leaq	LC45(%rip), %rdi
	xorl	%eax, %eax
	call	_err_sysexit
LVL143:
L138:
LBE117:
LBE121:
LBE139:
LBE148:
LM175:
	addq	$2408, %rsp
LCFI24:
	xorl	%eax, %eax
	popq	%rbx
LCFI25:
	popq	%rbp
LCFI26:
	popq	%r12
LCFI27:
	popq	%r13
LCFI28:
	popq	%r14
LCFI29:
	popq	%r15
LCFI30:
	ret
LVL144:
	.align 4
L50:
LCFI31:
LM176:
	movl	$1, 32(%rsp)
	jmp	L43
LVL145:
L190:
LM177:
	movl	$32, %esi
	movq	%rbx, %rdi
	call	_strchr
LVL146:
	testq	%rax, %rax
	je	L194
LM178:
	leaq	LC27(%rip), %rsi
	movq	%rbx, %rdi
	call	_strtok
LVL147:
LM179:
	leaq	LC27(%rip), %rsi
	xorl	%edi, %edi
	call	_strtok
LVL148:
LM180:
	movq	%rax, %rdi
	call	_chdir
LVL149:
	cmpl	$-1, %eax
	je	L195
LVL150:
L63:
LBB149:
LBB101:
LM181:
	leaq	LC55(%rip), %rdi
	movl	$8, %ecx
	movq	%rbx, %rsi
	repz cmpsb
	jne	L103
LVL151:
L120:
LBE101:
LBE149:
LM182:
	leaq	LC53(%rip), %rdi
	call	_getenv
LVL152:
LM183:
	testq	%rax, %rax
	je	L196
LM184:
	movq	%rax, 176(%rsp)
	jmp	L65
LVL153:
L100:
LM185:
	testl	%r14d, %r14d
	je	L101
LVL154:
L102:
LM186:
	movl	112(%rsp), %edi
	call	_close
LVL155:
LM187:
	movl	116(%rsp), %edi
	call	_close
LVL156:
L103:
LM188:
	movl	$1024, %edx
	xorl	%esi, %esi
	movq	%rbx, %rdi
	call	_memset
LVL157:
	jmp	L57
LVL158:
L86:
LBB150:
LBB140:
LBB122:
LBB118:
LM189:
	movq	%rbx, -8(%rbp)
LVL159:
L115:
LBE118:
LM190:
	leal	1(%r13), %eax
LVL160:
	addq	$8, %r14
	addq	$8, %rbp
	cmpl	%eax, %r12d
	je	L197
	movl	%eax, %r13d
LVL161:
	jmp	L89
LVL162:
L123:
	leaq	256(%rsp), %r12
LBE122:
LBE140:
LBE150:
LM191:
	movl	$1, %ebp
	jmp	L80
LVL163:
L188:
LM192:
	leaq	LC18(%rip), %rsi
	xorl	%eax, %eax
LVL164:
	leaq	LC19(%rip), %rdi
	call	_printf
LVL165:
	jmp	L41
LVL166:
L194:
LM193:
	call	_getuid
LVL167:
	movl	%eax, %edi
	call	_getpwuid
LVL168:
LM194:
	movq	48(%rax), %rdi
	call	_chdir
LVL169:
	addl	$1, %eax
	jne	L63
LM195:
	leaq	LC26(%rip), %rdi
	call	_perror
LVL170:
	jmp	L63
LVL171:
L191:
LM196:
	leaq	112(%rsp), %rdi
	call	_pipe
LVL172:
	addl	$1, %eax
	je	L198
L77:
LM197:
	call	_fork
LVL173:
	movl	%eax, 36(%rsp)
LVL174:
	jmp	L78
LVL175:
L195:
LM198:
	leaq	LC28(%rip), %rdi
	call	_perror
LVL176:
	jmp	L63
LVL177:
L193:
LBB151:
LBB141:
LBB123:
LBB113:
LM199:
	leaq	LC42(%rip), %rcx
	movl	$120, %edx
	leaq	LC8(%rip), %rsi
	leaq	___func__.3171(%rip), %rdi
	call	___assert_rtn
LVL178:
L192:
LBE113:
LBE123:
LBE141:
LBE151:
LM200:
	leaq	96(%rsp), %rsi
	xorl	%edx, %edx
	movl	$1, %edi
LM201:
	movl	$524288, 96(%rsp)
LM202:
	call	_sigprocmask
LVL179:
	jmp	L79
LVL180:
L197:
	movl	68(%rsp), %r14d
	movl	%r13d, %r12d
LVL181:
	movq	72(%rsp), %rbx
LVL182:
L85:
LBB152:
LBB142:
LM203:
	movq	56(%rsp), %rax
	movslq	%r12d, %r10
	cmpq	$0, -8(%rax,%r10,8)
	je	L199
LM204:
	movq	56(%rsp), %rax
LBB124:
LBB125:
LM205:
	leaq	LC48(%rip), %rdi
	xorl	%ebp, %ebp
LBE125:
LBE124:
LM206:
	movq	$0, (%rax,%r10,8)
LVL183:
LBB129:
LBB128:
LM207:
	call	_puts
LVL184:
	movq	24(%rsp), %r13
LVL185:
L92:
LBB126:
LBB127:
LM208:
	leaq	LC49(%rip), %rdi
	movl	%ebp, %esi
	xorl	%eax, %eax
	call	_printf
LVL186:
LM209:
	movq	0(%r13,%rbp,8), %r12
LVL187:
LM210:
	movq	(%r12), %rsi
	testq	%rsi, %rsi
	je	L95
	.align 4
L149:
LM211:
	leaq	LC41(%rip), %rdi
	addq	$8, %r12
LVL188:
	xorl	%eax, %eax
	call	_printf
LVL189:
LM212:
	movq	(%r12), %rsi
	testq	%rsi, %rsi
	jne	L149
L95:
LM213:
	movl	$10, %edi
	addq	$1, %rbp
LVL190:
	call	_putchar
LVL191:
LBE127:
LM214:
	cmpl	%ebp, 64(%rsp)
	jg	L92
LBE126:
LM215:
	leaq	LC50(%rip), %rdi
	call	_puts
LVL192:
LM216:
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	call	_fflush
LVL193:
LBE128:
LBE129:
LBB130:
LBB131:
LM217:
	call	_fork
LVL194:
	testl	%eax, %eax
	js	L200
LM218:
	je	L201
LVL195:
L97:
LBE131:
LBE130:
LM219:
	movq	24(%rsp), %rdi
	call	_free
LVL196:
LM220:
	movq	56(%rsp), %rdi
	call	_free
LVL197:
LBE142:
LBE152:
LBB153:
LBB154:
LM221:
	call	_getpid
LVL198:
	movq	40(%rsp), %r12
	movl	%eax, %ebp
LVL199:
	jmp	L98
LVL200:
L99:
LM222:
	movl	%eax, %ecx
	movq	___stderrp@GOTPCREL(%rip), %rax
LVL201:
	movl	%ebp, %edx
	movl	320(%rsp), %r8d
	leaq	LC51(%rip), %rsi
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	_fprintf
LVL202:
L98:
LM223:
	xorl	%edx, %edx
	xorl	%edi, %edi
	movq	%r12, %rsi
	call	_waitpid
LVL203:
	cmpl	$-1, %eax
	jne	L99
LVL204:
LBE154:
LBE153:
LM224:
	cmpl	$0, 36(%rsp)
	jne	L100
LM225:
	subl	$1, %r14d
LVL205:
	je	L202
L101:
LM226:
	movq	48(%rsp), %rsi
	xorl	%edx, %edx
	movl	_foreground(%rip), %edi
	call	_waitpid
LVL206:
LM227:
	leaq	208(%rsp), %rdi
	xorl	%esi, %esi
	call	_gettimeofday
LVL207:
LM228:
	movq	208(%rsp), %rax
LM229:
	movl	$1000, %ecx
LM230:
	subq	192(%rsp), %rax
LM231:
	leaq	LC52(%rip), %rdi
LM232:
	imulq	$1000000, %rax, %rdx
	movslq	216(%rsp), %rax
	addq	%rdx, %rax
	movslq	200(%rsp), %rdx
	subq	%rdx, %rax
LVL208:
LM233:
	cqto
	idivq	%rcx
LVL209:
	movq	%rax, %rsi
	xorl	%eax, %eax
	call	_printf
LVL210:
LM234:
	cmpl	$1, _isSignal(%rip)
	jne	L103
LBB155:
LM235:
	leaq	96(%rsp), %rsi
	xorl	%edx, %edx
	movl	$2, %edi
	call	_sigprocmask
LVL211:
	leaq	108(%rsp), %rbp
	movl	$20, 108(%rsp)
LVL212:
L122:
LBB156:
LBB157:
LBB158:
LM236:
	orl	$-1, %edi
	movl	$1, %edx
	movq	%rbp, %rsi
	call	_waitpid
LVL213:
LM237:
	testl	%eax, %eax
	jle	L103
LM238:
	cmpl	_foreground(%rip), %eax
	je	L122
LM239:
	movl	108(%rsp), %edx
	andl	$127, %edx
	cmpl	$127, %edx
	je	L122
LM240:
	leaq	LC23(%rip), %rdi
	movl	%eax, %esi
	xorl	%eax, %eax
LVL214:
	call	_printf
LVL215:
	jmp	L122
LVL216:
L124:
LBE158:
LBE157:
LBE156:
LBE155:
LBB159:
LBB143:
LM241:
	movl	$1, 64(%rsp)
LM242:
	xorl	%r12d, %r12d
LVL217:
	jmp	L85
LVL218:
L198:
LBE143:
LBE159:
LM243:
	leaq	LC38(%rip), %rdi
	call	_perror
LVL219:
	jmp	L77
LVL220:
L200:
LBB160:
LBB144:
LBB134:
LBB132:
LM244:
	leaq	LC10(%rip), %rdi
	xorl	%eax, %eax
LVL221:
	call	_err_syswarn.constprop.6
LVL222:
	jmp	L97
LVL223:
L196:
LBE132:
LBE134:
LBE144:
LBE160:
LM245:
	cmpl	$0, 32(%rsp)
	leaq	LC17(%rip), %rdx
	leaq	LC29(%rip), %rax
LVL224:
	cmove	%rdx, %rax
	movq	%rax, 176(%rsp)
L65:
LVL225:
LM246:
	leaq	LC30(%rip), %rbx
LM247:
	movl	$1, %edi
LBB161:
LBB162:
LM248:
	xorl	%ebp, %ebp
LBE162:
LBE161:
LM249:
	call	_malloc
LVL226:
LM250:
	leaq	176(%rsp), %r13
LM251:
	movq	%rbx, 288(%rsp)
LBB177:
LBB175:
LM252:
	xorl	%ebx, %ebx
LBE175:
LBE177:
LM253:
	movb	$0, (%rax)
LM254:
	leaq	LC31(%rip), %rsi
LM255:
	movq	%rax, 304(%rsp)
LM256:
	leaq	144(%rsp), %rax
LVL227:
	movq	%rax, 320(%rsp)
LM257:
	leaq	288(%rsp), %rax
	movq	%rax, 328(%rsp)
LM258:
	leaq	160(%rsp), %rax
LM259:
	movq	%rsi, 296(%rsp)
	leaq	128(%rsp), %r14
LM260:
	movq	$0, 312(%rsp)
LM261:
	movq	%rax, 336(%rsp)
LM262:
	movq	%r13, 344(%rsp)
LVL228:
L73:
LBB178:
LBB176:
LM263:
	movq	%r14, %rdi
	call	_pipe
LVL229:
	addl	$1, %eax
	je	L203
LM264:
	movl	132(%rsp), %r12d
LVL230:
LBB163:
LBB164:
LM265:
	call	_fork
LVL231:
	testl	%eax, %eax
	jne	L67
LBE164:
LBE163:
LM266:
	movslq	%ebx, %rbx
LVL232:
LBB170:
LBB165:
LM267:
	testl	%ebp, %ebp
LBE165:
LBE170:
LM268:
	leaq	320(%rsp,%rbx,8), %rbx
LVL233:
LBB171:
LBB166:
LM269:
	jne	L204
LVL234:
L68:
LM270:
	cmpl	$1, %r12d
	je	L70
LM271:
	movl	$1, %esi
	movl	%r12d, %edi
	call	_dup2
LVL235:
	testl	%eax, %eax
	js	L205
LM272:
	movl	%r12d, %edi
	call	_close
LVL236:
L70:
LM273:
	movq	(%rbx), %rbx
	movq	(%rbx), %rbp
LVL237:
	call	_getpid
LVL238:
	leaq	LC35(%rip), %rsi
	movl	%eax, %edx
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	%rbp, %rcx
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	_fprintf
LVL239:
LM274:
	movq	(%rbx), %rdi
	movq	%rbx, %rsi
	call	_execvp
LVL240:
LM275:
	movq	(%rbx), %rsi
	leaq	LC36(%rip), %rdi
	xorl	%eax, %eax
	call	_err_syserr
LVL241:
L204:
LM276:
	xorl	%esi, %esi
	movl	%ebp, %edi
	call	_dup2
LVL242:
	testl	%eax, %eax
	js	L206
LM277:
	movl	%ebp, %edi
	call	_close
LVL243:
	jmp	L68
LVL244:
L67:
LM278:
	js	L207
LVL245:
LBE166:
LBE171:
LM279:
	movl	132(%rsp), %edi
LM280:
	addl	$1, %ebx
LVL246:
LM281:
	call	_close
LVL247:
LM282:
	cmpl	$3, %ebx
LM283:
	movl	128(%rsp), %ebp
LVL248:
LM284:
	jne	L73
LM285:
	xorl	%esi, %esi
	movl	%ebp, %edi
	call	_dup2
LVL249:
	testl	%eax, %eax
	js	L208
LM286:
	movq	176(%rsp), %rbx
LVL250:
	call	_getpid
LVL251:
	leaq	LC35(%rip), %rsi
	movl	%eax, %edx
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	%rbx, %rcx
	movq	(%rax), %rdi
	xorl	%eax, %eax
	call	_fprintf
LVL252:
LM287:
	movq	176(%rsp), %rdi
	movq	%r13, %rsi
	call	_execvp
LVL253:
LM288:
	movq	176(%rsp), %rsi
	leaq	LC36(%rip), %rdi
	xorl	%eax, %eax
	call	_err_syserr
LVL254:
L206:
LBB172:
LBB167:
LM289:
	movq	(%rbx), %rax
	leaq	LC33(%rip), %rdi
	movq	(%rax), %rsi
	xorl	%eax, %eax
	call	_err_syserr
LVL255:
L208:
LBE167:
LBE172:
LM290:
	movq	176(%rsp), %rsi
	leaq	LC33(%rip), %rdi
	xorl	%eax, %eax
	call	_err_syserr
LVL256:
L207:
LBB173:
LBB168:
LM291:
	leaq	LC37(%rip), %rdi
	xorl	%eax, %eax
LVL257:
	call	_err_syserr
LVL258:
L203:
LBE168:
LBE173:
LM292:
	leaq	LC32(%rip), %rdi
	xorl	%eax, %eax
	call	_err_syserr
LVL259:
L205:
LBB174:
LBB169:
LM293:
	movq	(%rbx), %rax
	leaq	LC34(%rip), %rdi
	movq	(%rax), %rsi
	xorl	%eax, %eax
	call	_err_syserr
LVL260:
L87:
LBE169:
LBE174:
LBE176:
LBE178:
LBB179:
LBB145:
LBB135:
LBB119:
LM294:
	cmpq	$0, -16(%rbp)
	je	L209
LVL261:
LM295:
	movl	64(%rsp), %ebx
LM296:
	movq	$0, -8(%rbp)
LVL262:
LM297:
	movq	24(%rsp), %rsi
	movslq	%ebx, %rax
	movq	%rbp, (%rsi,%rax,8)
	movl	%ebx, %eax
	addl	$1, %eax
LVL263:
	movl	%eax, 64(%rsp)
	jmp	L115
LVL264:
L201:
LBE119:
LBE135:
LBB136:
LBB133:
LM298:
	movq	24(%rsp), %rsi
	movl	64(%rsp), %edi
	call	_exec_nth_command
LVL265:
L209:
LBE133:
LBE136:
LBB137:
LBB120:
LM299:
	leaq	LC46(%rip), %rdi
	xorl	%eax, %eax
	call	_err_sysexit
LVL266:
L202:
LBE120:
LBE137:
LBE145:
LBE179:
LM300:
	movl	112(%rsp), %edi
	xorl	%esi, %esi
	call	_dup2
LVL267:
LM301:
	movl	112(%rsp), %edi
	call	_close
LVL268:
LM302:
	movl	116(%rsp), %edi
	call	_close
LVL269:
	jmp	L102
LVL270:
L199:
LBB180:
LBB146:
LM303:
	leaq	LC47(%rip), %rdi
	xorl	%eax, %eax
	call	_err_sysexit
LVL271:
LBE146:
LBE180:
LFE22:
	.section __TEXT,__text_cold,regular,pure_instructions
LCOLDE56:
	.section __TEXT,__text_startup,regular,pure_instructions
LHOTE56:
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
LC57:
	.ascii "<undefined>\0"
	.data
	.align 3
_arg0:
	.quad	LC57
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
	.byte	0xa0,0x13
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
	.byte	0xa0,0x13
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
	.long	0x1b5e
	.word	0x2
	.set L$set$96,Ldebug_abbrev0-Lsection__debug_abbrev
	.long L$set$96
	.byte	0x8
	.byte	0x1
	.ascii "GNU C11 5.3.0 -fPIC -feliminate-unused-debug-symbols -mmacosx-version-min=10.11.4 -mtune=core2 -g -O3 -std=c11\0"
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
	.long	0xf1f
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
	.set L$set$117,LLST9-Lsection__debug_loc
	.long L$set$117
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1f
	.set L$set$118,LASF5-Lsection__debug_str
	.long L$set$118
	.byte	0x1
	.byte	0x4a
	.byte	0x1
	.byte	0x1
	.long	0xf62
	.byte	0x17
	.ascii "ncmds\0"
	.byte	0x1
	.byte	0x4a
	.long	0x115
	.byte	0x17
	.ascii "cmds\0"
	.byte	0x1
	.byte	0x4a
	.long	0xf62
	.byte	0x17
	.ascii "output\0"
	.byte	0x1
	.byte	0x4a
	.long	0xf68
	.byte	0x20
	.set L$set$119,LASF3-Lsection__debug_str
	.long L$set$119
	.long	0xf7e
	.byte	0x1
	.set L$set$120,LASF5-Lsection__debug_str
	.long L$set$120
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0xcca
	.byte	0x9
	.byte	0x8
	.long	0x115
	.byte	0x4
	.long	0x1a4
	.long	0xf7e
	.byte	0x5
	.long	0x198
	.byte	0x11
	.byte	0
	.byte	0x14
	.long	0xf6e
	.byte	0x27
	.ascii "exec_nth_command\0"
	.byte	0x1
	.byte	0x2f
	.byte	0x1
	.quad	LFB3
	.quad	LFE3
	.set L$set$121,LLST10-Lsection__debug_loc
	.long L$set$121
	.long	0x105f
	.byte	0x28
	.ascii "ncmds\0"
	.byte	0x1
	.byte	0x2f
	.long	0x115
	.set L$set$122,LLST11-Lsection__debug_loc
	.long L$set$122
	.byte	0x28
	.ascii "cmds\0"
	.byte	0x1
	.byte	0x2f
	.long	0xf62
	.set L$set$123,LLST12-Lsection__debug_loc
	.long L$set$123
	.byte	0x30
	.set L$set$124,LASF3-Lsection__debug_str
	.long L$set$124
	.long	0x106f
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
	.set L$set$125,LLST13-Lsection__debug_loc
	.long L$set$125
	.byte	0x29
	.ascii "input\0"
	.byte	0x1
	.byte	0x35
	.long	0xb5c
	.byte	0x2
	.byte	0x91
	.byte	0x50
	.byte	0x2c
	.long	0xf1f
	.quad	LBB25
	.quad	LBE25
	.byte	0x2d
	.long	0xf45
	.set L$set$126,LLST14-Lsection__debug_loc
	.long L$set$126
	.byte	0x2d
	.long	0xf39
	.set L$set$127,LLST15-Lsection__debug_loc
	.long L$set$127
	.byte	0x2d
	.long	0xf2c
	.set L$set$128,LLST16-Lsection__debug_loc
	.long L$set$128
	.byte	0x2e
	.quad	LBB26
	.quad	LBE26
	.byte	0x32
	.long	0xf53
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x4
	.long	0x1a4
	.long	0x106f
	.byte	0x5
	.long	0x198
	.byte	0x10
	.byte	0
	.byte	0x14
	.long	0x105f
	.byte	0x33
	.long	0xc53
	.quad	LFB23
	.quad	LFE23
	.set L$set$129,LLST17-Lsection__debug_loc
	.long L$set$129
	.long	0x10e4
	.byte	0x2d
	.long	0xc68
	.set L$set$130,LLST18-Lsection__debug_loc
	.long L$set$130
	.byte	0x1d
	.byte	0x34
	.long	0xc74
	.byte	0x2
	.byte	0x91
	.byte	0x48
	.byte	0x35
	.long	0xc68
	.byte	0x2c
	.long	0xe53
	.quad	LBB31
	.quad	LBE31
	.byte	0x35
	.long	0xe74
	.byte	0x35
	.long	0xe69
	.byte	0x2e
	.quad	LBB32
	.quad	LBE32
	.byte	0x2f
	.long	0xe7f
	.set L$set$131,LLST19-Lsection__debug_loc
	.long L$set$131
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
	.long	0x1128
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
	.long	0x116a
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
	.set L$set$132,LASF4-Lsection__debug_str
	.long L$set$132
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
	.long	0x11e2
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
	.long	0xf62
	.byte	0x1e
	.set L$set$133,LASF1-Lsection__debug_str
	.long L$set$133
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
	.set L$set$134,LASF6-Lsection__debug_str
	.long L$set$134
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x1
	.long	0x1222
	.byte	0x17
	.ascii "ncmds\0"
	.byte	0x1
	.byte	0x55
	.long	0x115
	.byte	0x17
	.ascii "cmds\0"
	.byte	0x1
	.byte	0x55
	.long	0xf62
	.byte	0x22
	.ascii "pid\0"
	.byte	0x1
	.byte	0x57
	.long	0x4a9
	.byte	0x20
	.set L$set$135,LASF3-Lsection__debug_str
	.long L$set$135
	.long	0x1232
	.byte	0x1
	.set L$set$136,LASF6-Lsection__debug_str
	.long L$set$136
	.byte	0
	.byte	0x4
	.long	0x1a4
	.long	0x1232
	.byte	0x5
	.long	0x198
	.byte	0xd
	.byte	0
	.byte	0x14
	.long	0x1222
	.byte	0x1c
	.ascii "dump_pipeline\0"
	.byte	0x1
	.byte	0x7b
	.byte	0x1
	.byte	0x1
	.long	0x127f
	.byte	0x17
	.ascii "cmdn\0"
	.byte	0x1
	.byte	0x7b
	.long	0x115
	.byte	0x17
	.ascii "cmdv\0"
	.byte	0x1
	.byte	0x7b
	.long	0xf62
	.byte	0x21
	.byte	0x22
	.ascii "i\0"
	.byte	0x1
	.byte	0x7e
	.long	0x115
	.byte	0x21
	.byte	0x1e
	.set L$set$137,LASF1-Lsection__debug_str
	.long L$set$137
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
	.set L$set$138,LLST20-Lsection__debug_loc
	.long L$set$138
	.long	0x1a6e
	.byte	0x26
	.ascii "argc\0"
	.byte	0x1
	.word	0x16d
	.long	0x115
	.set L$set$139,LLST21-Lsection__debug_loc
	.long L$set$139
	.byte	0x26
	.ascii "argv\0"
	.byte	0x1
	.word	0x16d
	.long	0xcca
	.set L$set$140,LLST22-Lsection__debug_loc
	.long L$set$140
	.byte	0x37
	.ascii "p\0"
	.byte	0x1
	.word	0x16f
	.long	0x483
	.set L$set$141,LLST23-Lsection__debug_loc
	.long L$set$141
	.byte	0x38
	.ascii "array\0"
	.byte	0x1
	.word	0x170
	.long	0x1a6e
	.byte	0x3
	.byte	0x91
	.byte	0xe0,0x6e
	.byte	0x38
	.ascii "line\0"
	.byte	0x1
	.word	0x171
	.long	0x1a7e
	.byte	0x3
	.byte	0x91
	.byte	0xc0,0x6f
	.byte	0x38
	.ascii "line2\0"
	.byte	0x1
	.word	0x172
	.long	0x1a7e
	.byte	0x3
	.byte	0x91
	.byte	0xc0,0x77
	.byte	0x1a
	.ascii "argv2\0"
	.byte	0x1
	.word	0x173
	.long	0x1a8f
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
	.set L$set$142,LLST24-Lsection__debug_loc
	.long L$set$142
	.byte	0x37
	.ascii "token3\0"
	.byte	0x1
	.word	0x176
	.long	0x483
	.set L$set$143,LLST25-Lsection__debug_loc
	.long L$set$143
	.byte	0x37
	.ascii "i\0"
	.byte	0x1
	.word	0x177
	.long	0x115
	.set L$set$144,LLST26-Lsection__debug_loc
	.long L$set$144
	.byte	0x37
	.ascii "tokenstr\0"
	.byte	0x1
	.word	0x178
	.long	0x483
	.set L$set$145,LLST27-Lsection__debug_loc
	.long L$set$145
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
	.set L$set$146,LLST28-Lsection__debug_loc
	.long L$set$146
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
	.long	0x1a9f
	.byte	0x3
	.byte	0x91
	.byte	0xf0,0x6d
	.byte	0x38
	.ascii "sort\0"
	.byte	0x1
	.word	0x17e
	.long	0x1a9f
	.byte	0x3
	.byte	0x91
	.byte	0x80,0x6e
	.byte	0x38
	.ascii "pager_cmd\0"
	.byte	0x1
	.word	0x17f
	.long	0x1a9f
	.byte	0x3
	.byte	0x91
	.byte	0x90,0x6e
	.byte	0x38
	.ascii "grep\0"
	.byte	0x1
	.word	0x180
	.long	0x1a6e
	.byte	0x3
	.byte	0x91
	.byte	0x80,0x6f
	.byte	0x37
	.ascii "time\0"
	.byte	0x1
	.word	0x181
	.long	0x18c
	.set L$set$147,LLST29-Lsection__debug_loc
	.long L$set$147
	.byte	0x3a
	.set L$set$148,LASF4-Lsection__debug_str
	.long L$set$148
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
	.set L$set$149,LLST30-Lsection__debug_loc
	.long L$set$149
	.byte	0x37
	.ascii "new_str\0"
	.byte	0x1
	.word	0x187
	.long	0x483
	.set L$set$150,LLST31-Lsection__debug_loc
	.long L$set$150
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
	.long	0x1aaf
	.set L$set$151,LLST32-Lsection__debug_loc
	.long L$set$151
	.byte	0x37
	.ascii "homedir\0"
	.byte	0x1
	.word	0x18b
	.long	0x8a3
	.set L$set$152,LLST33-Lsection__debug_loc
	.long L$set$152
	.byte	0x1a
	.ascii "cmd\0"
	.byte	0x1
	.word	0x18c
	.long	0x1ab5
	.byte	0x38
	.ascii "cmd2\0"
	.byte	0x1
	.word	0x18d
	.long	0x1ac5
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
	.set L$set$153,LLST34-Lsection__debug_loc
	.long L$set$153
	.byte	0x37
	.ascii "pagerValue\0"
	.byte	0x1
	.word	0x192
	.long	0x483
	.set L$set$154,LLST35-Lsection__debug_loc
	.long L$set$154
	.byte	0x37
	.ascii "ret\0"
	.byte	0x1
	.word	0x193
	.long	0x115
	.set L$set$155,LLST36-Lsection__debug_loc
	.long L$set$155
	.byte	0x37
	.ascii "pathValue\0"
	.byte	0x1
	.word	0x194
	.long	0x483
	.set L$set$156,LLST37-Lsection__debug_loc
	.long L$set$156
	.byte	0x37
	.ascii "pathValue2\0"
	.byte	0x1
	.word	0x195
	.long	0x483
	.set L$set$157,LLST38-Lsection__debug_loc
	.long L$set$157
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
	.long	0x15e5
	.byte	0x2d
	.long	0xbd4
	.set L$set$158,LLST39-Lsection__debug_loc
	.long L$set$158
	.byte	0x2e
	.quad	LBB78
	.quad	LBE78
	.byte	0x34
	.long	0xbe5
	.byte	0x3
	.byte	0x91
	.byte	0xc0,0x77
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0xd52
	.quad	LBB85
	.quad	LBE85
	.long	0x163a
	.byte	0x2d
	.long	0xd64
	.set L$set$159,LLST40-Lsection__debug_loc
	.long L$set$159
	.byte	0x2e
	.quad	LBB86
	.quad	LBE86
	.byte	0x32
	.long	0xd71
	.byte	0x2e
	.quad	LBB87
	.quad	LBE87
	.byte	0x2f
	.long	0xd7c
	.set L$set$160,LLST41-Lsection__debug_loc
	.long L$set$160
	.byte	0
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0xd52
	.quad	LBB88
	.quad	LBE88
	.long	0x168f
	.byte	0x2d
	.long	0xd64
	.set L$set$161,LLST42-Lsection__debug_loc
	.long L$set$161
	.byte	0x2e
	.quad	LBB89
	.quad	LBE89
	.byte	0x32
	.long	0xd71
	.byte	0x2e
	.quad	LBB90
	.quad	LBE90
	.byte	0x2f
	.long	0xd7c
	.set L$set$162,LLST43-Lsection__debug_loc
	.long L$set$162
	.byte	0
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0xbf5
	.quad	LBB91
	.quad	LBE91
	.long	0x16d6
	.byte	0x2d
	.long	0xc0c
	.set L$set$163,LLST44-Lsection__debug_loc
	.long L$set$163
	.byte	0x2e
	.quad	LBB92
	.quad	LBE92
	.byte	0x2f
	.long	0xc1b
	.set L$set$164,LLST45-Lsection__debug_loc
	.long L$set$164
	.byte	0x2f
	.long	0xc25
	.set L$set$165,LLST46-Lsection__debug_loc
	.long L$set$165
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0xcd5
	.quad	LBB93
	.quad	LBE93
	.long	0x16fe
	.byte	0x35
	.long	0xcf6
	.byte	0x2d
	.long	0xced
	.set L$set$166,LLST47-Lsection__debug_loc
	.long L$set$166
	.byte	0
	.byte	0x3b
	.long	0xcd5
	.quad	LBB97
	.quad	LBE97
	.long	0x1722
	.byte	0x35
	.long	0xcf6
	.byte	0x35
	.long	0xced
	.byte	0
	.byte	0x3b
	.long	0xcd5
	.quad	LBB99
	.quad	LBE99
	.long	0x1746
	.byte	0x35
	.long	0xcf6
	.byte	0x35
	.long	0xced
	.byte	0
	.byte	0x3b
	.long	0xc30
	.quad	LBB102
	.quad	LBE102
	.long	0x1769
	.byte	0x2d
	.long	0xc45
	.set L$set$167,LLST48-Lsection__debug_loc
	.long L$set$167
	.byte	0
	.byte	0x3b
	.long	0x116a
	.quad	LBB106
	.quad	LBE106
	.long	0x191c
	.byte	0x2d
	.long	0x118e
	.set L$set$168,LLST49-Lsection__debug_loc
	.long L$set$168
	.byte	0x2d
	.long	0x1182
	.set L$set$169,LLST50-Lsection__debug_loc
	.long L$set$169
	.byte	0x2e
	.quad	LBB107
	.quad	LBE107
	.byte	0x2f
	.long	0x119a
	.set L$set$170,LLST51-Lsection__debug_loc
	.long L$set$170
	.byte	0x2f
	.long	0x11a6
	.set L$set$171,LLST52-Lsection__debug_loc
	.long L$set$171
	.byte	0x2f
	.long	0x11b1
	.set L$set$172,LLST53-Lsection__debug_loc
	.long L$set$172
	.byte	0x2f
	.long	0x11bd
	.set L$set$173,LLST54-Lsection__debug_loc
	.long L$set$173
	.byte	0x3b
	.long	0xc80
	.quad	LBB108
	.quad	LBE108
	.long	0x1836
	.byte	0x35
	.long	0xc8d
	.byte	0x2d
	.long	0xca4
	.set L$set$174,LLST55-Lsection__debug_loc
	.long L$set$174
	.byte	0x2d
	.long	0xc98
	.set L$set$175,LLST56-Lsection__debug_loc
	.long L$set$175
	.byte	0x2e
	.quad	LBB109
	.quad	LBE109
	.byte	0x34
	.long	0xcb0
	.byte	0x9
	.byte	0x3
	.quad	___func__.3171
	.byte	0x2e
	.quad	LBB110
	.quad	LBE110
	.byte	0x2f
	.long	0xcbf
	.set L$set$176,LLST57-Lsection__debug_loc
	.long L$set$176
	.byte	0
	.byte	0
	.byte	0
	.byte	0x3c
	.quad	LBB116
	.quad	LBE116
	.long	0x1870
	.byte	0x2f
	.long	0x11ca
	.set L$set$177,LLST58-Lsection__debug_loc
	.long L$set$177
	.byte	0x2e
	.quad	LBB117
	.quad	LBE117
	.byte	0x2f
	.long	0x11d4
	.set L$set$178,LLST59-Lsection__debug_loc
	.long L$set$178
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0x1237
	.quad	LBB124
	.quad	LBE124
	.long	0x18d2
	.byte	0x2d
	.long	0x125a
	.set L$set$179,LLST60-Lsection__debug_loc
	.long L$set$179
	.byte	0x2d
	.long	0x124e
	.set L$set$180,LLST61-Lsection__debug_loc
	.long L$set$180
	.byte	0x2e
	.quad	LBB126
	.quad	LBE126
	.byte	0x2f
	.long	0x1267
	.set L$set$181,LLST62-Lsection__debug_loc
	.long L$set$181
	.byte	0x2e
	.quad	LBB127
	.quad	LBE127
	.byte	0x2f
	.long	0x1271
	.set L$set$182,LLST63-Lsection__debug_loc
	.long L$set$182
	.byte	0
	.byte	0
	.byte	0
	.byte	0x2c
	.long	0x11e2
	.quad	LBB130
	.quad	LBE130
	.byte	0x2d
	.long	0x11fc
	.set L$set$183,LLST64-Lsection__debug_loc
	.long L$set$183
	.byte	0x2d
	.long	0x11ef
	.set L$set$184,LLST65-Lsection__debug_loc
	.long L$set$184
	.byte	0x2e
	.quad	LBB131
	.quad	LBE131
	.byte	0x2f
	.long	0x1208
	.set L$set$185,LLST66-Lsection__debug_loc
	.long L$set$185
	.byte	0x32
	.long	0x1213
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x3b
	.long	0x1128
	.quad	LBB153
	.quad	LBE153
	.long	0x1963
	.byte	0x2e
	.quad	LBB154
	.quad	LBE154
	.byte	0x2f
	.long	0x1142
	.set L$set$186,LLST67-Lsection__debug_loc
	.long L$set$186
	.byte	0x2f
	.long	0x1150
	.set L$set$187,LLST68-Lsection__debug_loc
	.long L$set$187
	.byte	0x34
	.long	0x115e
	.byte	0x3
	.byte	0x91
	.byte	0xa0,0x6f
	.byte	0
	.byte	0
	.byte	0x3c
	.quad	LBB155
	.quad	LBE155
	.long	0x19d4
	.byte	0x1a
	.ascii "a\0"
	.byte	0x1
	.word	0x296
	.long	0x115
	.byte	0x2c
	.long	0xd52
	.quad	LBB156
	.quad	LBE156
	.byte	0x2d
	.long	0xd64
	.set L$set$188,LLST69-Lsection__debug_loc
	.long L$set$188
	.byte	0x2e
	.quad	LBB157
	.quad	LBE157
	.byte	0x32
	.long	0xd71
	.byte	0x2e
	.quad	LBB158
	.quad	LBE158
	.byte	0x2f
	.long	0xd7c
	.set L$set$189,LLST70-Lsection__debug_loc
	.long L$set$189
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x2c
	.long	0xd00
	.quad	LBB161
	.quad	LBE161
	.byte	0x35
	.long	0xd15
	.byte	0x2d
	.long	0xd1f
	.set L$set$190,LLST71-Lsection__debug_loc
	.long L$set$190
	.byte	0x2e
	.quad	LBB162
	.quad	LBE162
	.byte	0x2f
	.long	0xd2b
	.set L$set$191,LLST72-Lsection__debug_loc
	.long L$set$191
	.byte	0x2f
	.long	0xd35
	.set L$set$192,LLST73-Lsection__debug_loc
	.long L$set$192
	.byte	0x34
	.long	0xd40
	.byte	0x3
	.byte	0x91
	.byte	0xe0,0x6d
	.byte	0x2c
	.long	0x10e4
	.quad	LBB163
	.quad	LBE163
	.byte	0x35
	.long	0x1111
	.byte	0x2d
	.long	0x1106
	.set L$set$193,LLST74-Lsection__debug_loc
	.long L$set$193
	.byte	0x2d
	.long	0x10fc
	.set L$set$194,LLST75-Lsection__debug_loc
	.long L$set$194
	.byte	0x2e
	.quad	LBB164
	.quad	LBE164
	.byte	0x2f
	.long	0x111c
	.set L$set$195,LLST76-Lsection__debug_loc
	.long L$set$195
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x4
	.long	0x483
	.long	0x1a7e
	.byte	0x5
	.long	0x198
	.byte	0x3
	.byte	0
	.byte	0x4
	.long	0x1a4
	.long	0x1a8f
	.byte	0x3d
	.long	0x198
	.word	0x3ff
	.byte	0
	.byte	0x4
	.long	0x483
	.long	0x1a9f
	.byte	0x5
	.long	0x198
	.byte	0x63
	.byte	0
	.byte	0x4
	.long	0x483
	.long	0x1aaf
	.byte	0x5
	.long	0x198
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x8
	.long	0x3b9
	.byte	0x4
	.long	0xb68
	.long	0x1ac5
	.byte	0x5
	.long	0x198
	.byte	0x2
	.byte	0
	.byte	0x4
	.long	0xb68
	.long	0x1ad5
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
	.long	0x1afd
	.byte	0x1
	.byte	0x1
	.byte	0x9
	.byte	0x8
	.long	0x8e5
	.byte	0x3e
	.ascii "__stdoutp\0"
	.byte	0xc
	.byte	0x9d
	.long	0x1afd
	.byte	0x1
	.byte	0x1
	.byte	0x3e
	.ascii "__stderrp\0"
	.byte	0xc
	.byte	0x9e
	.long	0x1afd
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
	.byte	0x6
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
	.byte	0x34
	.byte	0
	.byte	0x31
	.byte	0x13
	.byte	0x2
	.byte	0xa
	.byte	0
	.byte	0
	.byte	0x35
	.byte	0x5
	.byte	0
	.byte	0x31
	.byte	0x13
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
	.quad	LVL22
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST9:
	.quad	LVL15
	.quad	LVL22
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST10:
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
LLST11:
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
LLST12:
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
LLST13:
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
LLST14:
	.quad	LVL37
	.quad	LVL42
	.word	0x1
	.byte	0x57
	.quad	0
	.quad	0
LLST15:
	.quad	LVL37
	.quad	LVL42
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST16:
	.quad	LVL41
	.quad	LVL42-1
	.word	0x1
	.byte	0x55
	.quad	0
	.quad	0
LLST17:
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
LLST18:
	.quad	LVL45
	.quad	LVL47-1
	.word	0x1
	.byte	0x55
	.quad	0
	.quad	0
LLST19:
	.quad	LVL48
	.quad	LVL54
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST20:
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
	.byte	0xa0,0x13
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
	.byte	0xa0,0x13
	.quad	0
	.quad	0
LLST21:
	.quad	LVL55
	.quad	LVL56
	.word	0x1
	.byte	0x55
	.quad	0
	.quad	0
LLST22:
	.quad	LVL55
	.quad	LVL57
	.word	0x1
	.byte	0x54
	.quad	LVL57
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0xf0,0x6c
	.quad	0
	.quad	0
LLST23:
	.quad	LVL117
	.quad	LVL120-1
	.word	0x1
	.byte	0x50
	.quad	LVL120
	.quad	LVL122
	.word	0x1
	.byte	0x50
	.quad	LVL162
	.quad	LVL163
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST24:
	.quad	LVL107
	.quad	LVL108
	.word	0x1
	.byte	0x51
	.quad	0
	.quad	0
LLST25:
	.quad	LVL67
	.quad	LVL68
	.word	0x1
	.byte	0x50
	.quad	LVL68
	.quad	LVL71
	.word	0x1
	.byte	0x53
	.quad	LVL71
	.quad	LVL73-1
	.word	0x1
	.byte	0x50
	.quad	LVL73-1
	.quad	LVL83
	.word	0x1
	.byte	0x53
	.quad	LVL89
	.quad	LVL91
	.word	0x1
	.byte	0x53
	.quad	LVL144
	.quad	LVL145
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST26:
	.quad	LVL118
	.quad	LVL121
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST27:
	.quad	LVL148
	.quad	LVL149-1
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST28:
	.quad	LVL112
	.quad	LVL137
	.word	0x1
	.byte	0x5e
	.quad	LVL137
	.quad	LVL143
	.word	0x3
	.byte	0x91
	.byte	0xa4,0x6d
	.quad	LVL158
	.quad	LVL162
	.word	0x3
	.byte	0x91
	.byte	0xa4,0x6d
	.quad	LVL162
	.quad	LVL163
	.word	0x1
	.byte	0x5e
	.quad	LVL171
	.quad	LVL175
	.word	0x1
	.byte	0x5e
	.quad	LVL177
	.quad	LVL180
	.word	0x1
	.byte	0x5e
	.quad	LVL180
	.quad	LVL182
	.word	0x3
	.byte	0x91
	.byte	0xa4,0x6d
	.quad	LVL216
	.quad	LVL220
	.word	0x1
	.byte	0x5e
	.quad	LVL260
	.quad	LVL264
	.word	0x3
	.byte	0x91
	.byte	0xa4,0x6d
	.quad	LVL265
	.quad	LVL266
	.word	0x3
	.byte	0x91
	.byte	0xa4,0x6d
	.quad	0
	.quad	0
LLST29:
	.quad	LVL208
	.quad	LVL209
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST30:
	.quad	LVL226
	.quad	LVL227
	.word	0x1
	.byte	0x50
	.quad	LVL227
	.quad	LVL228
	.word	0x3
	.byte	0x91
	.byte	0x90,0x6f
	.quad	0
	.quad	0
LLST31:
	.quad	LVL68
	.quad	LVL69-1
	.word	0x1
	.byte	0x50
	.quad	LVL69-1
	.quad	LVL72
	.word	0x1
	.byte	0x5d
	.quad	LVL75
	.quad	LVL76-1
	.word	0x1
	.byte	0x50
	.quad	LVL76-1
	.quad	LVL81
	.word	0x1
	.byte	0x5d
	.quad	LVL89
	.quad	LVL91
	.word	0x1
	.byte	0x5d
	.quad	0
	.quad	0
LLST32:
	.quad	LVL168
	.quad	LVL169-1
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST33:
	.quad	LVL168
	.quad	LVL169-1
	.word	0x2
	.byte	0x70
	.byte	0x30
	.quad	0
	.quad	0
LLST34:
	.quad	LVL84
	.quad	LVL89
	.word	0x3
	.byte	0x91
	.byte	0x84,0x6d
	.quad	LVL91
	.quad	LVL144
	.word	0x3
	.byte	0x91
	.byte	0x84,0x6d
	.quad	LVL145
	.quad	LVL163
	.word	0x3
	.byte	0x91
	.byte	0x84,0x6d
	.quad	LVL166
	.quad	LVL174
	.word	0x3
	.byte	0x91
	.byte	0x84,0x6d
	.quad	LVL174
	.quad	LVL175
	.word	0x1
	.byte	0x50
	.quad	LVL175
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0x84,0x6d
	.quad	0
	.quad	0
LLST35:
	.quad	LVL152
	.quad	LVL153
	.word	0x1
	.byte	0x50
	.quad	LVL223
	.quad	LVL224
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST36:
	.quad	LVL81
	.quad	LVL89
	.word	0x3
	.byte	0x91
	.byte	0x80,0x6d
	.quad	LVL91
	.quad	LVL144
	.word	0x3
	.byte	0x91
	.byte	0x80,0x6d
	.quad	LVL145
	.quad	LVL163
	.word	0x3
	.byte	0x91
	.byte	0x80,0x6d
	.quad	LVL166
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0x80,0x6d
	.quad	0
	.quad	0
LLST37:
	.quad	LVL61
	.quad	LVL62
	.word	0x1
	.byte	0x50
	.quad	LVL62
	.quad	LVL63-1
	.word	0x1
	.byte	0x51
	.quad	LVL63-1
	.quad	LVL67
	.word	0x1
	.byte	0x53
	.quad	LVL163
	.quad	LVL164
	.word	0x1
	.byte	0x50
	.quad	LVL164
	.quad	LVL166
	.word	0x1
	.byte	0x53
	.quad	0
	.quad	0
LLST38:
	.quad	LVL65
	.quad	LVL66-1
	.word	0x1
	.byte	0x50
	.quad	LVL66-1
	.quad	LVL84
	.word	0x1
	.byte	0x56
	.quad	LVL89
	.quad	LVL91
	.word	0x1
	.byte	0x56
	.quad	LVL144
	.quad	LVL145
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST39:
	.quad	LVL77
	.quad	LVL78-1
	.word	0x1
	.byte	0x55
	.quad	LVL78-1
	.quad	LVL78
	.word	0x1
	.byte	0x5d
	.quad	0
	.quad	0
LLST40:
	.quad	LVL85
	.quad	LVL89
	.word	0x2
	.byte	0x7f
	.byte	0
	.quad	0
	.quad	0
LLST41:
	.quad	LVL86
	.quad	LVL87
	.word	0x1
	.byte	0x50
	.quad	LVL87
	.quad	LVL88-1
	.word	0x1
	.byte	0x54
	.quad	0
	.quad	0
LLST42:
	.quad	LVL95
	.quad	LVL99
	.word	0x3
	.byte	0x77
	.byte	0
	.byte	0x6
	.quad	0
	.quad	0
LLST43:
	.quad	LVL96
	.quad	LVL97
	.word	0x1
	.byte	0x50
	.quad	LVL97
	.quad	LVL98-1
	.word	0x1
	.byte	0x54
	.quad	0
	.quad	0
LLST44:
	.quad	LVL100
	.quad	LVL104
	.word	0x3
	.byte	0x91
	.byte	0xe8,0x6c
	.quad	0
	.quad	0
LLST45:
	.quad	LVL100
	.quad	LVL101
	.word	0x3
	.byte	0x91
	.byte	0xe8,0x6c
	.quad	LVL101
	.quad	LVL105
	.word	0x1
	.byte	0x51
	.quad	0
	.quad	0
LLST46:
	.quad	LVL100
	.quad	LVL101
	.word	0x3
	.byte	0x91
	.byte	0xe8,0x6c
	.quad	LVL101
	.quad	LVL106
	.word	0x1
	.byte	0x52
	.quad	0
	.quad	0
LLST47:
	.quad	LVL104
	.quad	LVL143
	.word	0x3
	.byte	0x91
	.byte	0xe8,0x6c
	.quad	LVL145
	.quad	LVL163
	.word	0x3
	.byte	0x91
	.byte	0xe8,0x6c
	.quad	LVL166
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0xe8,0x6c
	.quad	0
	.quad	0
LLST48:
	.quad	LVL115
	.quad	LVL116
	.word	0x4
	.byte	0x91
	.byte	0xf0,0x6c
	.byte	0x6
	.quad	0
	.quad	0
LLST49:
	.quad	LVL123
	.quad	LVL136
	.word	0x1
	.byte	0x5c
	.quad	LVL136
	.quad	LVL138
	.word	0x1
	.byte	0x5d
	.quad	LVL138
	.quad	LVL139
	.word	0x1
	.byte	0x5e
	.quad	LVL177
	.quad	LVL178
	.word	0x1
	.byte	0x5c
	.quad	LVL216
	.quad	LVL217
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST50:
	.quad	LVL123
	.quad	LVL124-1
	.word	0x1
	.byte	0x51
	.quad	LVL124-1
	.quad	LVL139
	.word	0x1
	.byte	0x56
	.quad	LVL139
	.quad	LVL143
	.word	0x1
	.byte	0x5c
	.quad	LVL158
	.quad	LVL162
	.word	0x1
	.byte	0x5c
	.quad	LVL177
	.quad	LVL178
	.word	0x1
	.byte	0x56
	.quad	LVL180
	.quad	LVL181
	.word	0x1
	.byte	0x5c
	.quad	LVL216
	.quad	LVL218
	.word	0x1
	.byte	0x56
	.quad	LVL260
	.quad	LVL264
	.word	0x1
	.byte	0x5c
	.quad	LVL265
	.quad	LVL266
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST51:
	.quad	LVL130
	.quad	LVL131
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	0
	.quad	0
LLST52:
	.quad	LVL133
	.quad	LVL135
	.word	0x1
	.byte	0x50
	.quad	LVL135
	.quad	LVL139
	.word	0x2
	.byte	0x74
	.byte	0
	.quad	LVL139
	.quad	LVL143
	.word	0x3
	.byte	0x91
	.byte	0x98,0x6d
	.quad	LVL158
	.quad	LVL162
	.word	0x3
	.byte	0x91
	.byte	0x98,0x6d
	.quad	LVL180
	.quad	LVL197
	.word	0x3
	.byte	0x91
	.byte	0x98,0x6d
	.quad	LVL216
	.quad	LVL218
	.word	0x1
	.byte	0x50
	.quad	LVL220
	.quad	LVL223
	.word	0x3
	.byte	0x91
	.byte	0x98,0x6d
	.quad	LVL260
	.quad	LVL266
	.word	0x3
	.byte	0x91
	.byte	0x98,0x6d
	.quad	LVL270
	.quad	LFE22
	.word	0x3
	.byte	0x91
	.byte	0x98,0x6d
	.quad	0
	.quad	0
LLST53:
	.quad	LVL139
	.quad	LVL143
	.word	0x3
	.byte	0x91
	.byte	0xa0,0x6d
	.quad	LVL158
	.quad	LVL162
	.word	0x3
	.byte	0x91
	.byte	0xa0,0x6d
	.quad	LVL180
	.quad	LVL182
	.word	0x3
	.byte	0x91
	.byte	0xa0,0x6d
	.quad	LVL260
	.quad	LVL262
	.word	0x3
	.byte	0x91
	.byte	0xa0,0x6d
	.quad	LVL263
	.quad	LVL264
	.word	0x1
	.byte	0x50
	.quad	LVL265
	.quad	LVL266
	.word	0x3
	.byte	0x91
	.byte	0xa0,0x6d
	.quad	0
	.quad	0
LLST54:
	.quad	LVL158
	.quad	LVL161
	.word	0x1
	.byte	0x5d
	.quad	LVL180
	.quad	LVL182
	.word	0x1
	.byte	0x5d
	.quad	LVL261
	.quad	LVL264
	.word	0x1
	.byte	0x5d
	.quad	0
	.quad	0
LLST55:
	.quad	LVL123
	.quad	LVL129
	.word	0x1
	.byte	0x5c
	.quad	LVL177
	.quad	LVL178
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST56:
	.quad	LVL123
	.quad	LVL124-1
	.word	0x1
	.byte	0x51
	.quad	LVL124-1
	.quad	LVL129
	.word	0x1
	.byte	0x56
	.quad	LVL177
	.quad	LVL178
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST57:
	.quad	LVL124
	.quad	LVL125
	.word	0x1
	.byte	0x5d
	.quad	0
	.quad	0
LLST58:
	.quad	LVL139
	.quad	LVL143
	.word	0x1
	.byte	0x5d
	.quad	LVL158
	.quad	LVL160
	.word	0x1
	.byte	0x5d
	.quad	LVL160
	.quad	LVL162
	.word	0x1
	.byte	0x50
	.quad	LVL180
	.quad	LVL182
	.word	0x1
	.byte	0x50
	.quad	LVL260
	.quad	LVL264
	.word	0x1
	.byte	0x5d
	.quad	LVL265
	.quad	LVL266
	.word	0x1
	.byte	0x5d
	.quad	0
	.quad	0
LLST59:
	.quad	LVL140
	.quad	LVL142
	.word	0x1
	.byte	0x53
	.quad	LVL158
	.quad	LVL159
	.word	0x1
	.byte	0x53
	.quad	0
	.quad	0
LLST60:
	.quad	LVL183
	.quad	LVL193
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	0
	.quad	0
LLST61:
	.quad	LVL183
	.quad	LVL193
	.word	0x3
	.byte	0x91
	.byte	0xa0,0x6d
	.quad	0
	.quad	0
LLST62:
	.quad	LVL185
	.quad	LVL190
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST63:
	.quad	LVL187
	.quad	LVL193
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST64:
	.quad	LVL193
	.quad	LVL195
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	LVL220
	.quad	LVL223
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	LVL264
	.quad	LVL265
	.word	0x3
	.byte	0x91
	.byte	0xf8,0x6c
	.quad	0
	.quad	0
LLST65:
	.quad	LVL193
	.quad	LVL195
	.word	0x3
	.byte	0x91
	.byte	0xa0,0x6d
	.quad	LVL220
	.quad	LVL223
	.word	0x3
	.byte	0x91
	.byte	0xa0,0x6d
	.quad	LVL264
	.quad	LVL265
	.word	0x3
	.byte	0x91
	.byte	0xa0,0x6d
	.quad	0
	.quad	0
LLST66:
	.quad	LVL194
	.quad	LVL195
	.word	0x1
	.byte	0x50
	.quad	LVL220
	.quad	LVL221
	.word	0x1
	.byte	0x50
	.quad	LVL264
	.quad	LVL265-1
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST67:
	.quad	LVL199
	.quad	LVL200
	.word	0x1
	.byte	0x50
	.quad	LVL200
	.quad	LVL204
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST68:
	.quad	LVL200
	.quad	LVL201
	.word	0x1
	.byte	0x50
	.quad	LVL201
	.quad	LVL202-1
	.word	0x1
	.byte	0x52
	.quad	LVL203
	.quad	LVL204
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
LLST69:
	.quad	LVL212
	.quad	LVL216
	.word	0x2
	.byte	0x76
	.byte	0
	.quad	0
	.quad	0
LLST70:
	.quad	LVL213
	.quad	LVL214
	.word	0x1
	.byte	0x50
	.quad	LVL214
	.quad	LVL215-1
	.word	0x1
	.byte	0x54
	.quad	0
	.quad	0
LLST71:
	.quad	LVL228
	.quad	LVL260
	.word	0x3
	.byte	0x91
	.byte	0x88,0x6d
	.quad	0
	.quad	0
LLST72:
	.quad	LVL228
	.quad	LVL233
	.word	0x1
	.byte	0x53
	.quad	LVL244
	.quad	LVL246
	.word	0x1
	.byte	0x53
	.quad	LVL248
	.quad	LVL250
	.word	0x1
	.byte	0x53
	.quad	LVL255
	.quad	LVL259
	.word	0x1
	.byte	0x53
	.quad	0
	.quad	0
LLST73:
	.quad	LVL228
	.quad	LVL237
	.word	0x1
	.byte	0x56
	.quad	LVL241
	.quad	LVL260
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST74:
	.quad	LVL230
	.quad	LVL245
	.word	0x1
	.byte	0x5c
	.quad	LVL254
	.quad	LVL255
	.word	0x1
	.byte	0x5c
	.quad	LVL256
	.quad	LVL258
	.word	0x1
	.byte	0x5c
	.quad	LVL259
	.quad	LVL260
	.word	0x1
	.byte	0x5c
	.quad	0
	.quad	0
LLST75:
	.quad	LVL230
	.quad	LVL237
	.word	0x1
	.byte	0x56
	.quad	LVL241
	.quad	LVL245
	.word	0x1
	.byte	0x56
	.quad	LVL254
	.quad	LVL255
	.word	0x1
	.byte	0x56
	.quad	LVL256
	.quad	LVL258
	.word	0x1
	.byte	0x56
	.quad	LVL259
	.quad	LVL260
	.word	0x1
	.byte	0x56
	.quad	0
	.quad	0
LLST76:
	.quad	LVL231
	.quad	LVL234
	.word	0x1
	.byte	0x50
	.quad	LVL241
	.quad	LVL242-1
	.word	0x1
	.byte	0x50
	.quad	LVL244
	.quad	LVL245
	.word	0x1
	.byte	0x50
	.quad	LVL256
	.quad	LVL257
	.word	0x1
	.byte	0x50
	.quad	0
	.quad	0
	.section __DWARF,__debug_pubnames,regular,debug
Lsection__debug_pubnames:
	.long	0x187
	.word	0x2
	.set L$set$196,Ldebug_info0-Lsection__debug_info
	.long L$set$196
	.long	0x1b62
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
	.long	0xf1f
	.ascii "exec_pipe_command\0"
	.long	0xf83
	.ascii "exec_nth_command\0"
	.long	0x10e4
	.ascii "spawn_proc\0"
	.long	0x1128
	.ascii "corpse_collector\0"
	.long	0x116a
	.ascii "exec_arguments\0"
	.long	0x11e2
	.ascii "exec_pipeline\0"
	.long	0x1237
	.ascii "dump_pipeline\0"
	.long	0x127f
	.ascii "main\0"
	.long	0x1ad5
	.ascii "arg0\0"
	.long	0x1b29
	.ascii "isSignal\0"
	.long	0x1b44
	.ascii "foreground\0"
	.long	0
	.section __DWARF,__debug_pubtypes,regular,debug
Lsection__debug_pubtypes:
	.long	0x37e
	.word	0x2
	.set L$set$197,Ldebug_info0-Lsection__debug_info
	.long L$set$197
	.long	0x1b62
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
	.set L$set$198,Ldebug_info0-Lsection__debug_info
	.long L$set$198
	.byte	0x8
	.byte	0
	.word	0
	.word	0
	.quad	Ltext0
	.set L$set$199,Letext0-Ltext0
	.quad L$set$199
	.quad	Ltext_cold0
	.set L$set$200,Letext_cold0-Ltext_cold0
	.quad L$set$200
	.quad	LFB22
	.set L$set$201,LFE22-LFB22
	.quad L$set$201
	.quad	0
	.quad	0
	.section __DWARF,__debug_line,regular,debug
Lsection__debug_line:
Ldebug_line0:
	.set L$set$202,LELT0-LSLT0
	.long L$set$202
LSLT0:
	.word	0x2
	.set L$set$203,LELTP0-LASLTP0
	.long L$set$203
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
	.byte	0x6a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM95
	.byte	0x3
	.byte	0xad,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM96
	.byte	0x6b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM97
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM98
	.byte	0x14
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM99
	.byte	0x26
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM100
	.byte	0x3
	.byte	0x54
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM101
	.byte	0x52
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM102
	.byte	0xcd
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM103
	.byte	0x3
	.byte	0xa8,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM104
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM105
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM106
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM107
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM108
	.byte	0x91
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM109
	.byte	0x2b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM110
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM111
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM112
	.byte	0x3
	.byte	0xe3,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM113
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM114
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM115
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM116
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM117
	.byte	0xac
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM118
	.byte	0x3
	.byte	0xfc,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM119
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM120
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM121
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM122
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM123
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM124
	.byte	0x13
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM125
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM126
	.byte	0x3
	.byte	0x91,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM127
	.byte	0x3
	.byte	0xf2,0x1
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM128
	.byte	0x3
	.byte	0x8e,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM129
	.byte	0x3
	.byte	0xf2,0x1
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM130
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM131
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM132
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM133
	.byte	0x3
	.byte	0x89,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM134
	.byte	0x3
	.byte	0xd9,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM135
	.byte	0x1f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM136
	.byte	0x23
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM137
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM138
	.byte	0x20
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM139
	.byte	0x3
	.byte	0xd3,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM140
	.byte	0x3
	.byte	0xb2,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM141
	.byte	0x3
	.byte	0xce,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM142
	.byte	0x3
	.byte	0xb2,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM143
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM144
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM145
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM146
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM147
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM148
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM149
	.byte	0x14
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM150
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM151
	.byte	0x3
	.byte	0x84,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM152
	.byte	0x3
	.byte	0xfc,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM153
	.byte	0x3
	.byte	0x84,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM154
	.byte	0x3
	.byte	0xfc,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM155
	.byte	0x3
	.byte	0x84,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM156
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM157
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM158
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM159
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM160
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM161
	.byte	0x2f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM162
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM163
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM164
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM165
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM166
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM167
	.byte	0x11
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM168
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM169
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM170
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM171
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM172
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM173
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM174
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM175
	.byte	0x3
	.byte	0x91,0x4
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM176
	.byte	0x3
	.byte	0x89,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM177
	.byte	0x48
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM178
	.byte	0x23
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM179
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM180
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM181
	.byte	0x3
	.byte	0xf2,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM182
	.byte	0x3
	.byte	0x9e,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM183
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM184
	.byte	0x24
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM185
	.byte	0x8b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM186
	.byte	0x32
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM187
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM188
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM189
	.byte	0x3
	.byte	0xf8,0x7b
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM190
	.byte	0x3
	.byte	0x74
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM191
	.byte	0x3
	.byte	0xcf,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM192
	.byte	0x3
	.byte	0xbe,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM193
	.byte	0x5e
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM194
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM195
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM196
	.byte	0x75
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM197
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM198
	.byte	0x3
	.byte	0xa7,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM199
	.byte	0x3
	.byte	0xfe,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM200
	.byte	0x3
	.byte	0xe6,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM201
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM202
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM203
	.byte	0x3
	.byte	0xc9,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM204
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM205
	.byte	0x3
	.byte	0x54
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM206
	.byte	0x43
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM207
	.byte	0x3
	.byte	0x54
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM208
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM209
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM210
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM211
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM212
	.byte	0x16
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM213
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM214
	.byte	0x11
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM215
	.byte	0x1f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM216
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM217
	.byte	0x3
	.byte	0x53
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM218
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM219
	.byte	0x68
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM220
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM221
	.byte	0x3
	.byte	0xb6,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM222
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM223
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM224
	.byte	0x3
	.byte	0x90,0x4
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM225
	.byte	0x1f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM226
	.byte	0x24
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM227
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM228
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM229
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM230
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM231
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM232
	.byte	0x15
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
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM236
	.byte	0x3
	.byte	0x9e,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM237
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM238
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM239
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM240
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM241
	.byte	0x3
	.byte	0xd4,0x7e
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM242
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM243
	.byte	0x3
	.byte	0xbd,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM244
	.byte	0x3
	.byte	0x8b,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM245
	.byte	0x3
	.byte	0xb2,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM246
	.byte	0x36
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM247
	.byte	0x11
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM248
	.byte	0x3
	.byte	0xea,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM249
	.byte	0x3
	.byte	0x96,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM250
	.byte	0x24
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM251
	.byte	0x10
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM252
	.byte	0x3
	.byte	0xe7,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM253
	.byte	0x3
	.byte	0x94,0x2
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM254
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM255
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM256
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM257
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM258
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM259
	.byte	0x12
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM260
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM261
	.byte	0x1a
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM262
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM263
	.byte	0x3
	.byte	0xe2,0x7d
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM264
	.byte	0x1c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM265
	.byte	0x3
	.byte	0x59
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM266
	.byte	0x3e
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM267
	.byte	0x3
	.byte	0x5b
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM268
	.byte	0x3c
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM269
	.byte	0x3
	.byte	0x5b
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM270
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM271
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM272
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM273
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM274
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM275
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM276
	.byte	0x3
	.byte	0x74
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM277
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM278
	.byte	0x23
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM279
	.byte	0x2d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM280
	.byte	0xf
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM281
	.byte	0x1f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM282
	.byte	0xf
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM283
	.byte	0x20
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM284
	.byte	0xe
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM285
	.byte	0x22
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM286
	.byte	0x1b
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM287
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM288
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM289
	.byte	0x3
	.byte	0x54
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM290
	.byte	0x3f
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM291
	.byte	0x3
	.byte	0x67
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM292
	.byte	0x27
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM293
	.byte	0x3
	.byte	0x67
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM294
	.byte	0x3
	.byte	0xa1,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM295
	.byte	0x1d
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM296
	.byte	0x15
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM297
	.byte	0x19
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM298
	.byte	0x3
	.byte	0xb9,0x7f
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM299
	.byte	0x59
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM300
	.byte	0x3
	.byte	0xe1,0x3
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM301
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM302
	.byte	0x18
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LM303
	.byte	0x3
	.byte	0xa5,0x7c
	.byte	0x1
	.byte	0
	.byte	0x9
	.byte	0x2
	.quad	LHOTE56
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
