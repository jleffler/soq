	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.file	1 "c_posix.c"
	.file	2 "/usr/include/i386" "_types.h"
	.file	3 "/usr/include/sys" "_types.h"
	.file	4 "/usr/include/sys/_types" "_pid_t.h"
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
Lfunc_begin0:
	.loc	1 366 0                 ## c_posix.c:366:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$2520, %rsp             ## imm = 0x9D8
Ltmp3:
	.cfi_offset %rbx, -56
Ltmp4:
	.cfi_offset %r12, -48
Ltmp5:
	.cfi_offset %r13, -40
Ltmp6:
	.cfi_offset %r14, -32
Ltmp7:
	.cfi_offset %r15, -24
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- %RSI
	movq	%rsi, -2528(%rbp)       ## 8-byte Spill
Ltmp8:
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
Ltmp9:
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:argc2 <- 0
	.loc	1 381 11 prologue_end   ## c_posix.c:381:11
	movaps	l_main.printenv(%rip), %xmm0
	movaps	%xmm0, -2304(%rbp)
	.loc	1 382 11                ## c_posix.c:382:11
	movaps	l_main.sort(%rip), %xmm0
	movaps	%xmm0, -2320(%rbp)
	.loc	1 383 11                ## c_posix.c:383:11
	movaps	l_main.pager_cmd(%rip), %xmm0
	movaps	%xmm0, -2336(%rbp)
Ltmp10:
	##DEBUG_VALUE: main:status <- 0
	.loc	1 386 9                 ## c_posix.c:386:9
	movl	$0, -2404(%rbp)
Ltmp11:
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:max <- 80
	xorps	%xmm0, %xmm0
	.loc	1 409 5                 ## c_posix.c:409:5
	movaps	%xmm0, -2464(%rbp)
Ltmp12:
	##DEBUG_VALUE: main:pid_temp <- 0
	.loc	1 412 21                ## c_posix.c:412:21
	leaq	_sighandler(%rip), %rax
	movq	%rax, -2464(%rbp)
	.loc	1 413 17                ## c_posix.c:413:17
	movl	$64, -2452(%rbp)
	leaq	-2464(%rbp), %rsi
Ltmp13:
	##DEBUG_VALUE: main:sa <- [%RSI+0]
	leaq	-2480(%rbp), %rdx
Ltmp14:
	##DEBUG_VALUE: main:osa <- [%RDX+0]
	.loc	1 414 5                 ## c_posix.c:414:5
	movl	$2, %edi
Ltmp15:
	callq	_sigaction
	.loc	1 417 17                ## c_posix.c:417:17
	leaq	L_.str.4(%rip), %rdi
	callq	_getenv
	movq	%rax, %rbx
Ltmp16:
	##DEBUG_VALUE: main:pathValue <- %RBX
	.loc	1 418 9                 ## c_posix.c:418:9
	testq	%rbx, %rbx
	je	LBB0_1
Ltmp17:
## BB#2:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue <- %RBX
	.loc	1 424 9                 ## c_posix.c:424:9
	leaq	L_.str.6(%rip), %rdi
Ltmp18:
	leaq	L_.str.4(%rip), %rsi
	xorl	%eax, %eax
	movq	%rbx, %rdx
	callq	_printf
	jmp	LBB0_3
Ltmp19:
LBB0_1:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue <- %RBX
	.loc	1 420 9                 ## c_posix.c:420:9
	leaq	L_.str.5(%rip), %rdi
Ltmp20:
	leaq	L_.str.4(%rip), %rsi
	xorl	%eax, %eax
	callq	_printf
Ltmp21:
LBB0_3:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue <- %RBX
	.loc	1 427 18                ## c_posix.c:427:18
	movq	%rbx, %rdi
Ltmp22:
	callq	_strdup
Ltmp23:
	##DEBUG_VALUE: main:pathValue2 <- %RAX
	.loc	1 428 14                ## c_posix.c:428:14
	movq	%rax, -2488(%rbp)       ## 8-byte Spill
	leaq	L_.str.7(%rip), %rsi
	movq	%rax, %rdi
Ltmp24:
	##DEBUG_VALUE: main:pathValue2 <- [%RBP+-2488]
	callq	_strtok
	movq	%rax, %r14
Ltmp25:
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:token3 <- %R14
	.loc	1 430 19                ## c_posix.c:430:19
	testq	%r14, %r14
	movl	$1, %eax
	je	LBB0_10
Ltmp26:
## BB#4:                                ## %.lr.ph30
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue2 <- [%RBP+-2488]
	##DEBUG_VALUE: main:token3 <- %R14
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 453 18                ## c_posix.c:453:18
	leaq	L_.str.7(%rip), %r12
	leaq	-192(%rbp), %r13
Ltmp27:
	.align	4, 0x90
LBB0_5:                                 ## =>This Inner Loop Header: Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue2 <- [%RBP+-2488]
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 432 31                ## c_posix.c:432:31
	movq	%r14, %rdi
Ltmp28:
	callq	_strlen
	.loc	1 432 64 is_stmt 0      ## c_posix.c:432:64
	leaq	6(%rax), %rdi
	.loc	1 432 24                ## c_posix.c:432:24
	callq	_malloc
	movq	%rax, %r15
Ltmp29:
	##DEBUG_VALUE: main:new_str <- %R15
	##DEBUG_VALUE: file_exist:filename <- %R15
	.loc	1 432 70                ## c_posix.c:432:70
	testq	%r15, %r15
Ltmp30:
	.loc	1 432 13                ## c_posix.c:432:13
	je	LBB0_7
Ltmp31:
## BB#6:                                ##   in Loop: Header=BB0_5 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue2 <- [%RBP+-2488]
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: file_exist:filename <- %R15
	##DEBUG_VALUE: main:new_str <- %R15
	.loc	1 434 24 is_stmt 1      ## c_posix.c:434:24
	movb	$0, (%r15)
	.loc	1 435 13                ## c_posix.c:435:13
	movq	$-1, %rdx
	movq	%r15, %rdi
Ltmp32:
	movq	%r14, %rsi
	callq	___strcat_chk
	movq	$-1, %rdx
	.loc	1 436 13                ## c_posix.c:436:13
	movq	%r15, %rdi
	leaq	L_.str.8(%rip), %rsi
	callq	___strcat_chk
Ltmp33:
	##DEBUG_VALUE: file_exist:buffer <- [%R13+0]
	.loc	1 353 12                ## c_posix.c:353:12
	movq	%r15, %rdi
	movq	%r13, %rsi
	callq	_stat$INODE64
	movl	%eax, %ebx
Ltmp34:
	##DEBUG_VALUE: main:ret <- 0
	##DEBUG_VALUE: main:breakloop <- 1
	.loc	1 443 13                ## c_posix.c:443:13
	movq	%r15, %rdi
	callq	_free
	xorl	%eax, %eax
	.loc	1 353 36                ## c_posix.c:353:36
Ltmp35:
	testl	%ebx, %ebx
	jne	LBB0_8
	jmp	LBB0_10
Ltmp36:
	.align	4, 0x90
LBB0_7:                                 ##   in Loop: Header=BB0_5 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue2 <- [%RBP+-2488]
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 451 13                ## c_posix.c:451:13
	leaq	L_str(%rip), %rdi
Ltmp37:
	callq	_puts
Ltmp38:
LBB0_8:                                 ##   in Loop: Header=BB0_5 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue2 <- [%RBP+-2488]
	##DEBUG_VALUE: main:ret <- 1
	xorl	%edi, %edi
Ltmp39:
	.loc	1 453 18                ## c_posix.c:453:18
	movq	%r12, %rsi
	callq	_strtok
	movq	%rax, %r14
Ltmp40:
	##DEBUG_VALUE: main:token3 <- %R14
	.loc	1 430 5                 ## c_posix.c:430:5
	testq	%r14, %r14
	jne	LBB0_5
Ltmp41:
## BB#9:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue2 <- [%RBP+-2488]
	##DEBUG_VALUE: main:ret <- 1
	movl	$1, %eax
Ltmp42:
LBB0_10:                                ## %._crit_edge.31
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:pathValue2 <- [%RBP+-2488]
	##DEBUG_VALUE: main:ret <- 1
	movl	%eax, -2532(%rbp)       ## 4-byte Spill
	.loc	1 455 5                 ## c_posix.c:455:5
	movq	-2488(%rbp), %rdi       ## 8-byte Reload
Ltmp43:
	callq	_free
	leaq	-192(%rbp), %r12
	.loc	1 321 25                ## c_posix.c:321:25
Ltmp44:
	leaq	L_.str.28(%rip), %r13
Ltmp45:
	.loc	1 117 25                ## c_posix.c:117:25
	leaq	L_.str.46(%rip), %r14
	.loc	1 117 9 is_stmt 0       ## c_posix.c:117:9
	leaq	L_.str.45(%rip), %r15
	movl	$0, -2516(%rbp)         ## 4-byte Folded Spill
	jmp	LBB0_11
Ltmp46:
LBB0_116:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 464 9 is_stmt 1       ## c_posix.c:464:9
	movl	$1024, %esi             ## imm = 0x400
	leaq	-1248(%rbp), %rdi
Ltmp47:
	.loc	1 683 9                 ## c_posix.c:683:9
	callq	___bzero
	.align	4, 0x90
LBB0_11:                                ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_12 Depth 2
                                        ##     Child Loop BB0_18 Depth 2
                                        ##     Child Loop BB0_23 Depth 2
                                        ##     Child Loop BB0_65 Depth 2
                                        ##     Child Loop BB0_75 Depth 2
                                        ##     Child Loop BB0_78 Depth 2
                                        ##     Child Loop BB0_82 Depth 2
                                        ##     Child Loop BB0_91 Depth 2
                                        ##       Child Loop BB0_93 Depth 3
                                        ##     Child Loop BB0_101 Depth 2
                                        ##     Child Loop BB0_108 Depth 2
Ltmp48:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: Janitor:status <- 20
	.loc	1 461 9                 ## c_posix.c:461:9
	movl	$20, -192(%rbp)
	jmp	LBB0_12
Ltmp49:
	.align	4, 0x90
LBB0_15:                                ##   in Loop: Header=BB0_12 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 1
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	xorl	%eax, %eax
	.loc	1 321 25                ## c_posix.c:321:25
Ltmp50:
	movq	%r13, %rdi
Ltmp51:
	movl	%ecx, %esi
	callq	_printf
Ltmp52:
LBB0_12:                                ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	##DEBUG_VALUE: a <- 1
	.loc	1 308 29                ## c_posix.c:308:29
	movl	$-1, %edi
	movl	$1, %edx
	movq	%r12, %rsi
	callq	_waitpid
	movl	%eax, %ecx
Ltmp53:
	##DEBUG_VALUE: pid_my1 <- %ECX
	.loc	1 313 17                ## c_posix.c:313:17
	testl	%ecx, %ecx
	jle	LBB0_16
Ltmp54:
## BB#13:                               ## %.lr.ph
                                        ##   in Loop: Header=BB0_12 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 1
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	.loc	1 315 21                ## c_posix.c:315:21
	cmpl	_foreground(%rip), %ecx
	je	LBB0_12
Ltmp55:
## BB#14:                               ##   in Loop: Header=BB0_12 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 1
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	.loc	1 319 48                ## c_posix.c:319:48
	movl	-192(%rbp), %eax
	.loc	1 319 25 is_stmt 0      ## c_posix.c:319:25
	andl	$127, %eax
	cmpl	$127, %eax
	je	LBB0_12
	jmp	LBB0_15
Ltmp56:
	.align	4, 0x90
LBB0_16:                                ## %Janitor.exit
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	xorl	%eax, %eax
	.loc	1 463 9 is_stmt 1       ## c_posix.c:463:9
	leaq	L_.str.10(%rip), %rdi
Ltmp57:
	callq	_printf
	.loc	1 464 9                 ## c_posix.c:464:9
	movl	$1024, %esi             ## imm = 0x400
	leaq	-1248(%rbp), %rbx
	movq	%rbx, %rdi
	callq	___bzero
	.loc	1 465 38                ## c_posix.c:465:38
Ltmp58:
	movq	___stdinp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdx
	.loc	1 465 14 is_stmt 0      ## c_posix.c:465:14
	movl	$1024, %esi             ## imm = 0x400
	movq	%rbx, %rdi
	callq	_fgets
	testq	%rax, %rax
	je	LBB0_117
Ltmp59:
## BB#17:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: Janitor:status <- 20
	.loc	1 469 9 is_stmt 1       ## c_posix.c:469:9
	movl	$20, -192(%rbp)
	jmp	LBB0_18
Ltmp60:
	.align	4, 0x90
LBB0_21:                                ##   in Loop: Header=BB0_18 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 1
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	xorl	%eax, %eax
	.loc	1 321 25                ## c_posix.c:321:25
Ltmp61:
	movq	%r13, %rdi
Ltmp62:
	movl	%ecx, %esi
	callq	_printf
Ltmp63:
LBB0_18:                                ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	##DEBUG_VALUE: a <- 1
	.loc	1 308 29                ## c_posix.c:308:29
	movl	$-1, %edi
	movl	$1, %edx
Ltmp64:
	.loc	1 308 29 is_stmt 0      ## c_posix.c:308:29
	movq	%r12, %rsi
	callq	_waitpid
	movl	%eax, %ecx
Ltmp65:
	##DEBUG_VALUE: pid_my1 <- %ECX
	.loc	1 313 17 is_stmt 1      ## c_posix.c:313:17
	testl	%ecx, %ecx
	jle	LBB0_22
Ltmp66:
## BB#19:                               ## %.lr.ph19
                                        ##   in Loop: Header=BB0_18 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 1
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	.loc	1 315 21                ## c_posix.c:315:21
	cmpl	_foreground(%rip), %ecx
	je	LBB0_18
Ltmp67:
## BB#20:                               ##   in Loop: Header=BB0_18 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 1
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	.loc	1 319 48                ## c_posix.c:319:48
	movl	-192(%rbp), %eax
	.loc	1 319 25 is_stmt 0      ## c_posix.c:319:25
	andl	$127, %eax
	cmpl	$127, %eax
	je	LBB0_18
	jmp	LBB0_21
Ltmp68:
	.align	4, 0x90
LBB0_22:                                ## %Janitor.exit6
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 464 9 is_stmt 1       ## c_posix.c:464:9
	movl	$1024, %edx             ## imm = 0x400
	leaq	-2272(%rbp), %rbx
	.loc	1 470 9                 ## c_posix.c:470:9
	movq	%rbx, %rdi
Ltmp69:
	leaq	-1248(%rbp), %rsi
	callq	_strncpy
	.loc	1 339 12                ## c_posix.c:339:12
Ltmp70:
	movb	-2272(%rbp), %dl
	.loc	1 339 15 is_stmt 0      ## c_posix.c:339:15
	testb	%dl, %dl
Ltmp71:
	.loc	1 457 5 is_stmt 1       ## c_posix.c:457:5
	leaq	-2271(%rbp), %rcx
	.loc	1 471 9                 ## c_posix.c:471:9
Ltmp72:
	movq	%rbx, %rax
	je	LBB0_24
	.align	4, 0x90
LBB0_23:                                ## %.lr.ph.i
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
Ltmp73:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 341 12                ## c_posix.c:341:12
	movb	%dl, (%rax)
	.loc	1 342 16                ## c_posix.c:342:16
Ltmp74:
	movzbl	%dl, %edx
	.loc	1 343 14                ## c_posix.c:343:14
	leaq	1(%rax), %rsi
Ltmp75:
	##DEBUG_VALUE: RemoveSpaces:i <- %RAX
	.loc	1 342 16                ## c_posix.c:342:16
	cmpl	$32, %edx
Ltmp76:
	.loc	1 342 13 is_stmt 0      ## c_posix.c:342:13
	cmovneq	%rsi, %rax
Ltmp77:
	.loc	1 339 12 is_stmt 1      ## c_posix.c:339:12
	movb	(%rcx), %dl
	.loc	1 339 5 is_stmt 0       ## c_posix.c:339:5
	incq	%rcx
	testb	%dl, %dl
	jne	LBB0_23
Ltmp78:
LBB0_24:                                ## %RemoveSpaces.exit
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 345 8 is_stmt 1       ## c_posix.c:345:8
	movb	$0, (%rax)
Ltmp79:
	.loc	1 234 34                ## c_posix.c:234:34
	movzbl	-2272(%rbp), %eax
	cmpl	$10, %eax
	je	LBB0_11
Ltmp80:
## BB#25:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	leaq	-1248(%rbp), %rbx
	.loc	1 476 18                ## c_posix.c:476:18
	movq	%rbx, %rdi
Ltmp81:
	callq	_strlen
Ltmp82:
	##DEBUG_VALUE: main:length <- %RAX
	.loc	1 477 13                ## c_posix.c:477:13
	movzbl	-1(%rax,%rbx), %ecx
	cmpl	$10, %ecx
	jne	LBB0_27
Ltmp83:
## BB#26:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:length <- %RAX
	.loc	1 479 30                ## c_posix.c:479:30
	movb	$0, -1249(%rbp,%rax)
Ltmp84:
LBB0_27:                                ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 481 13                ## c_posix.c:481:13
	movq	%rbx, %rdi
Ltmp85:
	leaq	L_.str.12(%rip), %rsi
	callq	_strcmp
	.loc	1 481 34 is_stmt 0      ## c_posix.c:481:34
	testl	%eax, %eax
	je	LBB0_117
Ltmp86:
## BB#28:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: StartsWith:b <- undef
	.loc	1 234 9 is_stmt 1       ## c_posix.c:234:9
	movl	$2, %edx
	movq	%rbx, %rdi
Ltmp87:
	leaq	L_.str.13(%rip), %rsi
	callq	_strncmp
	xorl	%r14d, %r14d
Ltmp88:
	.loc	1 486 13                ## c_posix.c:486:13
	testl	%eax, %eax
	jne	LBB0_35
## BB#29:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp89:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 489 17                ## c_posix.c:489:17
	movl	$32, %esi
	movq	%rbx, %rdi
Ltmp90:
	callq	_strchr
Ltmp91:
	.loc	1 489 17 is_stmt 0      ## c_posix.c:489:17
	testq	%rax, %rax
	je	LBB0_30
## BB#32:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp92:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 501 28 is_stmt 1      ## c_posix.c:501:28
	movq	%rbx, %rdi
Ltmp93:
	leaq	L_.str(%rip), %r14
	movq	%r14, %rsi
	callq	_strtok
	xorl	%edi, %edi
	.loc	1 502 28                ## c_posix.c:502:28
	movq	%r14, %rsi
	callq	_strtok
Ltmp94:
	##DEBUG_VALUE: main:tokenstr <- %RAX
	.loc	1 504 21                ## c_posix.c:504:21
	movq	%rax, %rdi
	callq	_chdir
Ltmp95:
	movl	$1, %r14d
Ltmp96:
	.loc	1 504 21 is_stmt 0      ## c_posix.c:504:21
	cmpl	$-1, %eax
	jne	LBB0_35
## BB#33:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp97:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 506 21 is_stmt 1      ## c_posix.c:506:21
	leaq	L_.str.15(%rip), %rdi
Ltmp98:
	jmp	LBB0_34
Ltmp99:
LBB0_30:                                ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 491 31                ## c_posix.c:491:31
	callq	_getuid
	.loc	1 491 22 is_stmt 0      ## c_posix.c:491:22
	movl	%eax, %edi
Ltmp100:
	callq	_getpwuid
Ltmp101:
	##DEBUG_VALUE: main:pw <- %RAX
	.loc	1 492 31 is_stmt 1      ## c_posix.c:492:31
	movq	48(%rax), %rdi
Ltmp102:
	##DEBUG_VALUE: main:homedir <- %RDI
	.loc	1 494 21                ## c_posix.c:494:21
	callq	_chdir
Ltmp103:
	movl	$1, %r14d
Ltmp104:
	.loc	1 494 21 is_stmt 0      ## c_posix.c:494:21
	cmpl	$-1, %eax
	je	LBB0_31
Ltmp105:
LBB0_35:                                ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: StartsWith:b <- undef
	.loc	1 234 9 is_stmt 1       ## c_posix.c:234:9
	movl	$8, %edx
	movq	%rbx, %rdi
Ltmp106:
	leaq	L_.str.16(%rip), %rsi
	callq	_strncmp
Ltmp107:
	.loc	1 516 13                ## c_posix.c:516:13
	testl	%eax, %eax
	je	LBB0_36
## BB#63:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp108:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	xorl	%r13d, %r13d
	.loc	1 568 13                ## c_posix.c:568:13
	testl	%r14d, %r14d
	movl	$4, %eax
	movl	$1, %edx
	je	LBB0_65
Ltmp109:
## BB#64:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 321 25                ## c_posix.c:321:25
	leaq	L_.str.28(%rip), %r13
Ltmp110:
	.loc	1 117 25                ## c_posix.c:117:25
	leaq	L_.str.46(%rip), %r14
	jmp	LBB0_116
Ltmp111:
	.align	4, 0x90
LBB0_65:                                ## %.preheader
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 581 25                ## c_posix.c:581:25
	movzbl	-1252(%rbp,%rax), %ecx
	cmpl	$38, %ecx
Ltmp112:
	##DEBUG_VALUE: main:isBackground <- 1
	movzbl	-1251(%rbp,%rax), %ecx
Ltmp113:
	.loc	1 581 21 is_stmt 0      ## c_posix.c:581:21
	cmovel	%edx, %r13d
	.loc	1 581 25                ## c_posix.c:581:25
Ltmp114:
	cmpl	$38, %ecx
	movzbl	-1250(%rbp,%rax), %ecx
Ltmp115:
	.loc	1 581 21                ## c_posix.c:581:21
	cmovel	%edx, %r13d
	.loc	1 581 25                ## c_posix.c:581:25
Ltmp116:
	cmpl	$38, %ecx
	movzbl	-1249(%rbp,%rax), %ecx
Ltmp117:
	.loc	1 581 21                ## c_posix.c:581:21
	cmovel	%edx, %r13d
	.loc	1 581 25                ## c_posix.c:581:25
Ltmp118:
	cmpl	$38, %ecx
	movzbl	-1248(%rbp,%rax), %ecx
Ltmp119:
	.loc	1 581 21                ## c_posix.c:581:21
	cmovel	%edx, %r13d
	.loc	1 581 25                ## c_posix.c:581:25
Ltmp120:
	cmpl	$38, %ecx
Ltmp121:
	.loc	1 581 21                ## c_posix.c:581:21
	cmovel	%edx, %r13d
Ltmp122:
	.loc	1 579 13 is_stmt 1      ## c_posix.c:579:13
	addq	$5, %rax
	cmpq	$84, %rax
	jne	LBB0_65
Ltmp123:
## BB#66:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 587 17                ## c_posix.c:587:17
	cmpl	$1, %r13d
	jne	LBB0_70
Ltmp124:
## BB#67:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	leaq	-2280(%rbp), %rdi
Ltmp125:
	.loc	1 590 21                ## c_posix.c:590:21
	callq	_pipe
Ltmp126:
	.loc	1 590 21 is_stmt 0      ## c_posix.c:590:21
	cmpl	$-1, %eax
Ltmp127:
	.loc	1 501 28 is_stmt 1      ## c_posix.c:501:28
	leaq	L_.str(%rip), %rbx
	je	LBB0_68
Ltmp128:
LBB0_69:                                ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 595 28                ## c_posix.c:595:28
	callq	_fork
	movl	%eax, -2516(%rbp)       ## 4-byte Spill
Ltmp129:
	##DEBUG_VALUE: main:pid_temp <- [%RBP+-2516]
	jmp	LBB0_74
Ltmp130:
LBB0_70:                                ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 597 22                ## c_posix.c:597:22
	testl	%r13d, %r13d
Ltmp131:
	.loc	1 501 28                ## c_posix.c:501:28
	leaq	L_.str(%rip), %rbx
	jne	LBB0_74
Ltmp132:
## BB#71:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:time_start <- undef
	xorl	%esi, %esi
	leaq	-2424(%rbp), %rdi
Ltmp133:
	.loc	1 599 17                ## c_posix.c:599:17
	callq	_gettimeofday
	.loc	1 601 21                ## c_posix.c:601:21
	cmpl	$1, _isSignal(%rip)
	jne	LBB0_73
## BB#72:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp134:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:time_start <- undef
	##DEBUG_VALUE: main:my_sig <- 524288
	##DEBUG_VALUE: __sigbits:__signo <- 20
	.loc	1 604 21                ## c_posix.c:604:21
	movl	$524288, -2444(%rbp)    ## imm = 0x80000
Ltmp135:
	##DEBUG_VALUE: main:my_sig <- undef
	movl	$1, %edi
Ltmp136:
	xorl	%edx, %edx
	leaq	-2444(%rbp), %rsi
	.loc	1 606 21                ## c_posix.c:606:21
	callq	_sigprocmask
Ltmp137:
LBB0_73:                                ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:time_start <- undef
	.loc	1 610 28                ## c_posix.c:610:28
	movl	-2516(%rbp), %eax       ## 4-byte Reload
	movl	%eax, _foreground(%rip)
Ltmp138:
LBB0_74:                                ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 612 25                ## c_posix.c:612:25
	movq	-2528(%rbp), %rax       ## 8-byte Reload
	movq	(%rax), %rax
	.loc	1 181 10                ## c_posix.c:181:10
Ltmp139:
	movq	%rax, _arg0(%rip)
Ltmp140:
	##DEBUG_VALUE: main:i <- 1
	leaq	-1248(%rbp), %rdi
Ltmp141:
	.loc	1 615 17                ## c_posix.c:615:17
	movq	%rbx, %rsi
	callq	_strtok
Ltmp142:
	##DEBUG_VALUE: main:p <- %RAX
	.loc	1 617 22                ## c_posix.c:617:22
	movq	$0, -224(%rbp)
	movl	$1, %r14d
	.loc	1 618 22                ## c_posix.c:618:22
	testq	%rax, %rax
	movl	$1, %ebx
	je	LBB0_77
Ltmp143:
	.align	4, 0x90
LBB0_75:                                ## %.lr.ph24
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 620 28                ## c_posix.c:620:28
	movq	%rax, -224(%rbp,%rbx,8)
Ltmp144:
	.loc	1 618 13                ## c_posix.c:618:13
	incq	%rbx
	xorl	%edi, %edi
Ltmp145:
	.loc	1 501 28                ## c_posix.c:501:28
	leaq	L_.str(%rip), %rsi
Ltmp146:
	.loc	1 621 21                ## c_posix.c:621:21
	callq	_strtok
Ltmp147:
	##DEBUG_VALUE: main:p <- %RAX
	.loc	1 618 13                ## c_posix.c:618:13
	testq	%rax, %rax
	jne	LBB0_75
Ltmp148:
## BB#76:                               ## %._crit_edge.loopexit
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	movl	%ebx, %r14d
Ltmp149:
LBB0_77:                                ## %._crit_edge
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 623 13                ## c_posix.c:623:13
	movslq	%r14d, %rbx
	.loc	1 623 22 is_stmt 0      ## c_posix.c:623:22
	movq	%rbx, -2512(%rbp)       ## 8-byte Spill
	movq	$0, -224(%rbp,%rbx,8)
	xorl	%eax, %eax
	.loc	1 115 5 is_stmt 1       ## c_posix.c:115:5
Ltmp150:
	leaq	L_.str.44(%rip), %rdi
Ltmp151:
	leaq	L_.str.37(%rip), %rsi
	movl	%ebx, %edx
	callq	_printf
Ltmp152:
	##DEBUG_VALUE: i <- 0
	.loc	1 116 5                 ## c_posix.c:116:5
	testl	%ebx, %ebx
	leaq	-224(%rbp), %rbx
	jle	LBB0_79
	.align	4, 0x90
LBB0_78:                                ## %.lr.ph.i.i
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
Ltmp153:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: i <- 0
	.loc	1 117 26                ## c_posix.c:117:26
	movq	(%rbx), %rsi
	.loc	1 117 34 is_stmt 0      ## c_posix.c:117:34
	testq	%rsi, %rsi
	.loc	1 117 25                ## c_posix.c:117:25
	leaq	L_.str.46(%rip), %rax
	cmoveq	%rax, %rsi
	xorl	%eax, %eax
	.loc	1 117 9                 ## c_posix.c:117:9
	movq	%r15, %rdi
Ltmp154:
	callq	_printf
Ltmp155:
	.loc	1 116 5 is_stmt 1       ## c_posix.c:116:5
	addq	$8, %rbx
	decl	%r14d
	jne	LBB0_78
Ltmp156:
LBB0_79:                                ## %dump_argv.exit.i
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 118 5                 ## c_posix.c:118:5
	movl	$10, %edi
Ltmp157:
	callq	_putchar
	.loc	1 119 12                ## c_posix.c:119:12
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	.loc	1 119 5 is_stmt 0       ## c_posix.c:119:5
	callq	_fflush
	movq	-2512(%rbp), %rbx       ## 8-byte Reload
Ltmp158:
	.loc	1 144 48 is_stmt 1      ## c_posix.c:144:48
	movl	%ebx, %eax
	shrl	$31, %eax
	addl	%ebx, %eax
	sarl	%eax
	.loc	1 144 42 is_stmt 0      ## c_posix.c:144:42
	movslq	%eax, %rdi
	.loc	1 144 40                ## c_posix.c:144:40
	shlq	$3, %rdi
	.loc	1 144 20                ## c_posix.c:144:20
	callq	_malloc
	movq	%rax, %r14
	.loc	1 145 39 is_stmt 1      ## c_posix.c:145:39
	movq	%r14, -2496(%rbp)       ## 8-byte Spill
	leaq	8(,%rbx,8), %rdi
	.loc	1 145 19 is_stmt 0      ## c_posix.c:145:19
	callq	_malloc
Ltmp159:
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	.loc	1 149 18 is_stmt 1      ## c_posix.c:149:18
	movq	%rax, -2504(%rbp)       ## 8-byte Spill
	movq	%rax, (%r14)
Ltmp160:
	##DEBUG_VALUE: i <- 1
	movl	$1, -2488(%rbp)         ## 4-byte Folded Spill
	xorl	%r15d, %r15d
	.loc	1 151 23                ## c_posix.c:151:23
Ltmp161:
	cmpl	$1, %ebx
	movl	$1, %r14d
	jle	LBB0_80
	.align	4, 0x90
LBB0_82:                                ## %.lr.ph.i.9
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
Ltmp162:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 1
	.loc	1 153 21                ## c_posix.c:153:21
	movq	-224(%rbp,%r14,8), %rbx
Ltmp163:
	##DEBUG_VALUE: arg <- %RBX
	xorl	%eax, %eax
	.loc	1 154 9                 ## c_posix.c:154:9
	leaq	L_.str.38(%rip), %rdi
Ltmp164:
	movl	%r14d, %esi
	movq	%rbx, %rdx
	callq	_printf
	.loc	1 155 13                ## c_posix.c:155:13
Ltmp165:
	movq	%rbx, %rdi
	leaq	L_.str.21(%rip), %rsi
	callq	_strcmp
Ltmp166:
	.loc	1 155 13 is_stmt 0      ## c_posix.c:155:13
	testl	%eax, %eax
	je	LBB0_83
Ltmp167:
## BB#87:                               ##   in Loop: Header=BB0_82 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- %R15D
	##DEBUG_VALUE: i <- 1
	##DEBUG_VALUE: arg <- %RBX
	.loc	1 163 9 is_stmt 1       ## c_posix.c:163:9
	movslq	%r15d, %rcx
	.loc	1 163 18 is_stmt 0      ## c_posix.c:163:18
	incl	%r15d
Ltmp168:
	movq	-2504(%rbp), %rax       ## 8-byte Reload
	.loc	1 163 22                ## c_posix.c:163:22
	movq	%rbx, (%rax,%rcx,8)
	.loc	1 164 13 is_stmt 1      ## c_posix.c:164:13
	testq	%rbx, %rbx
	jne	LBB0_89
	jmp	LBB0_88
Ltmp169:
	.align	4, 0x90
LBB0_83:                                ##   in Loop: Header=BB0_82 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 1
	.loc	1 157 17                ## c_posix.c:157:17
	cmpq	$1, %r14
	movq	-2504(%rbp), %rax       ## 8-byte Reload
	je	LBB0_122
Ltmp170:
## BB#84:                               ##   in Loop: Header=BB0_82 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 1
	.loc	1 159 17                ## c_posix.c:159:17
	movslq	%r15d, %rcx
	.loc	1 159 32 is_stmt 0      ## c_posix.c:159:32
	cmpq	$0, -8(%rax,%rcx,8)
Ltmp171:
	.loc	1 159 17                ## c_posix.c:159:17
	je	LBB0_86
Ltmp172:
## BB#85:                               ## %.thread.i.10
                                        ##   in Loop: Header=BB0_82 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 1
	.loc	1 163 18 is_stmt 1      ## c_posix.c:163:18
	incl	%r15d
	.loc	1 163 22 is_stmt 0      ## c_posix.c:163:22
	movq	$0, (%rax,%rcx,8)
Ltmp173:
LBB0_88:                                ##   in Loop: Header=BB0_82 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 1
	.loc	1 165 29 is_stmt 1      ## c_posix.c:165:29
	movslq	%r15d, %rcx
	leaq	(%rax,%rcx,8), %rsi
Ltmp174:
	##DEBUG_VALUE: exec_arguments:cmdn <- [%RBP+-2488]
	movl	-2488(%rbp), %edx       ## 4-byte Reload
Ltmp175:
	##DEBUG_VALUE: exec_arguments:cmdn <- %EDX
	.loc	1 165 13 is_stmt 0      ## c_posix.c:165:13
	movslq	%edx, %rcx
	.loc	1 165 22                ## c_posix.c:165:22
	incl	%edx
Ltmp176:
	movl	%edx, -2488(%rbp)       ## 4-byte Spill
	.loc	1 165 26                ## c_posix.c:165:26
	movq	-2496(%rbp), %rdx       ## 8-byte Reload
	movq	%rsi, (%rdx,%rcx,8)
Ltmp177:
LBB0_89:                                ##   in Loop: Header=BB0_82 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 1
	.loc	1 151 5 is_stmt 1       ## c_posix.c:151:5
	incq	%r14
	.loc	1 151 23 is_stmt 0      ## c_posix.c:151:23
Ltmp178:
	cmpq	-2512(%rbp), %r14       ## 8-byte Folded Reload
	jl	LBB0_82
Ltmp179:
LBB0_80:                                ## %._crit_edge.i
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	.loc	1 167 9 is_stmt 1       ## c_posix.c:167:9
	movslq	%r15d, %rcx
	.loc	1 167 24 is_stmt 0      ## c_posix.c:167:24
	cmpq	$0, -8(%rax,%rcx,8)
	je	LBB0_81
Ltmp180:
## BB#90:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	.loc	1 169 16 is_stmt 1      ## c_posix.c:169:16
	movq	$0, (%rax,%rcx,8)
	movq	%rax, -2504(%rbp)       ## 8-byte Spill
	.loc	1 125 5                 ## c_posix.c:125:5
Ltmp181:
	leaq	L_str.58(%rip), %rdi
Ltmp182:
	callq	_puts
Ltmp183:
	##DEBUG_VALUE: i <- 0
	.loc	1 126 5                 ## c_posix.c:126:5
	cmpl	$0, -2488(%rbp)         ## 4-byte Folded Reload
	movl	$0, %r14d
	jle	LBB0_95
	.align	4, 0x90
LBB0_91:                                ## %.lr.ph5.i.i
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Loop Header: Depth=2
                                        ##       Child Loop BB0_93 Depth 3
Ltmp184:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 0
	xorl	%eax, %eax
	.loc	1 128 9                 ## c_posix.c:128:9
Ltmp185:
	leaq	L_.str.51(%rip), %rdi
Ltmp186:
	movl	%r14d, %esi
	callq	_printf
	.loc	1 129 23                ## c_posix.c:129:23
	movq	-2496(%rbp), %rax       ## 8-byte Reload
	movq	(%rax,%r14,8), %rbx
Ltmp187:
	##DEBUG_VALUE: args <- %RBX
	.loc	1 130 16                ## c_posix.c:130:16
	movq	(%rbx), %rsi
	.loc	1 130 22 is_stmt 0      ## c_posix.c:130:22
	testq	%rsi, %rsi
Ltmp188:
	.loc	1 117 9 is_stmt 1       ## c_posix.c:117:9
	leaq	L_.str.45(%rip), %r15
	je	LBB0_94
Ltmp189:
## BB#92:                               ## %.lr.ph.i.2.i.preheader
                                        ##   in Loop: Header=BB0_91 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 0
	##DEBUG_VALUE: args <- %RBX
	.loc	1 131 34                ## c_posix.c:131:34
	addq	$8, %rbx
Ltmp190:
	.align	4, 0x90
LBB0_93:                                ## %.lr.ph.i.2.i
                                        ##   Parent Loop BB0_11 Depth=1
                                        ##     Parent Loop BB0_91 Depth=2
                                        ## =>    This Inner Loop Header: Depth=3
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 0
	xorl	%eax, %eax
	.loc	1 131 13 is_stmt 0      ## c_posix.c:131:13
	movq	%r15, %rdi
Ltmp191:
	callq	_printf
	.loc	1 130 16 is_stmt 1      ## c_posix.c:130:16
	movq	(%rbx), %rsi
	.loc	1 130 9 is_stmt 0       ## c_posix.c:130:9
	addq	$8, %rbx
	testq	%rsi, %rsi
	jne	LBB0_93
Ltmp192:
LBB0_94:                                ## %._crit_edge.i.6.i
                                        ##   in Loop: Header=BB0_91 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 0
	.loc	1 118 5 is_stmt 1       ## c_posix.c:118:5
	movl	$10, %edi
Ltmp193:
	.loc	1 132 9                 ## c_posix.c:132:9
	callq	_putchar
Ltmp194:
	.loc	1 126 5                 ## c_posix.c:126:5
	incq	%r14
	cmpl	-2488(%rbp), %r14d      ## 4-byte Folded Reload
	jne	LBB0_91
Ltmp195:
LBB0_95:                                ## %dump_pipeline.exit.i
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	.loc	1 134 5                 ## c_posix.c:134:5
	leaq	L_str.59(%rip), %rdi
Ltmp196:
	callq	_puts
Ltmp197:
	.loc	1 119 12                ## c_posix.c:119:12
	movq	___stdoutp@GOTPCREL(%rip), %rax
Ltmp198:
	.loc	1 135 12                ## c_posix.c:135:12
	movq	(%rax), %rdi
	.loc	1 135 5 is_stmt 0       ## c_posix.c:135:5
	callq	_fflush
Ltmp199:
	.loc	1 88 5 is_stmt 1        ## c_posix.c:88:5
	cmpl	$0, -2488(%rbp)         ## 4-byte Folded Reload
	jle	LBB0_123
## BB#96:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp200:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	.loc	1 90 16                 ## c_posix.c:90:16
	callq	_fork
Ltmp201:
	##DEBUG_VALUE: exec_pipeline:pid <- %EAX
	.loc	1 90 9 is_stmt 0        ## c_posix.c:90:9
	testl	%eax, %eax
	js	LBB0_97
Ltmp202:
## BB#98:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	.loc	1 105 9 is_stmt 1       ## c_posix.c:105:9
	leaq	L_.str.57(%rip), %r14
	movq	%r14, %r15
	jne	LBB0_100
Ltmp203:
## BB#99:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	.loc	1 94 5                  ## c_posix.c:94:5
	movl	-2488(%rbp), %edi       ## 4-byte Reload
Ltmp204:
	movq	-2496(%rbp), %rsi       ## 8-byte Reload
	callq	_exec_nth_command
	jmp	LBB0_100
LBB0_97:                                ## %.thread.i.i
                                        ##   in Loop: Header=BB0_11 Depth=1
Ltmp205:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	xorl	%eax, %eax
	.loc	1 91 9                  ## c_posix.c:91:9
Ltmp206:
	callq	_err_syswarn
Ltmp207:
	.loc	1 105 9                 ## c_posix.c:105:9
	leaq	L_.str.57(%rip), %r14
	movq	%r14, %r15
Ltmp208:
LBB0_100:                               ## %exec_arguments.exit
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	.loc	1 173 5                 ## c_posix.c:173:5
	movq	-2496(%rbp), %rdi       ## 8-byte Reload
Ltmp209:
	callq	_free
	.loc	1 174 5                 ## c_posix.c:174:5
	movq	-2504(%rbp), %rdi       ## 8-byte Reload
	callq	_free
Ltmp210:
	.loc	1 100 20                ## c_posix.c:100:20
	callq	_getpid
	movl	%eax, %ebx
Ltmp211:
	##DEBUG_VALUE: corpse_collector:parent <- %EBX
	##DEBUG_VALUE: corpse_collector:status <- [%R12+0]
	xorl	%edi, %edi
	xorl	%edx, %edx
	.loc	1 103 22                ## c_posix.c:103:22
	movq	%r12, %rsi
	callq	_waitpid
	movl	%eax, %ecx
Ltmp212:
	##DEBUG_VALUE: corpse_collector:corpse <- %ECX
	.loc	1 103 46 is_stmt 0      ## c_posix.c:103:46
	cmpl	$-1, %ecx
	.loc	1 105 17 is_stmt 1      ## c_posix.c:105:17
Ltmp213:
	movq	___stderrp@GOTPCREL(%rip), %r14
	je	LBB0_102
Ltmp214:
	.align	4, 0x90
LBB0_101:                               ## %.lr.ph.i.11
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	movq	(%r14), %rdi
Ltmp215:
	.loc	1 106 43                ## c_posix.c:106:43
	movl	-192(%rbp), %r8d
	xorl	%eax, %eax
	.loc	1 105 9                 ## c_posix.c:105:9
	movq	%r15, %rsi
	movl	%ebx, %edx
	callq	_fprintf
Ltmp216:
	##DEBUG_VALUE: corpse_collector:status <- [%R12+0]
	xorl	%edi, %edi
	xorl	%edx, %edx
Ltmp217:
	.loc	1 103 22                ## c_posix.c:103:22
	movq	%r12, %rsi
	callq	_waitpid
	movl	%eax, %ecx
Ltmp218:
	##DEBUG_VALUE: corpse_collector:corpse <- %ECX
	.loc	1 103 5 is_stmt 0       ## c_posix.c:103:5
	cmpl	$-1, %ecx
	jne	LBB0_101
Ltmp219:
LBB0_102:                               ## %corpse_collector.exit
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 627 17 is_stmt 1      ## c_posix.c:627:17
	cmpl	$1, %r13d
	jne	LBB0_105
Ltmp220:
## BB#103:                              ## %corpse_collector.exit
                                        ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	cmpl	$0, -2516(%rbp)         ## 4-byte Folded Reload
	jne	LBB0_105
Ltmp221:
## BB#104:                              ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 641 26                ## c_posix.c:641:26
	movl	-2280(%rbp), %edi
Ltmp222:
	xorl	%esi, %esi
	.loc	1 641 21 is_stmt 0      ## c_posix.c:641:21
	callq	_dup2
	.loc	1 642 27 is_stmt 1      ## c_posix.c:642:27
	movl	-2280(%rbp), %edi
	.loc	1 642 21 is_stmt 0      ## c_posix.c:642:21
	callq	_close
	.loc	1 643 27 is_stmt 1      ## c_posix.c:643:27
	movl	-2276(%rbp), %edi
	.loc	1 643 21 is_stmt 0      ## c_posix.c:643:21
	callq	_close
Ltmp223:
LBB0_105:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 650 17 is_stmt 1      ## c_posix.c:650:17
	testl	%r13d, %r13d
	je	LBB0_106
Ltmp224:
## BB#112:                              ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 675 22                ## c_posix.c:675:22
	cmpl	$1, %r13d
	jne	LBB0_114
Ltmp225:
## BB#113:                              ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 677 23                ## c_posix.c:677:23
	movl	-2280(%rbp), %edi
Ltmp226:
	.loc	1 677 17 is_stmt 0      ## c_posix.c:677:17
	callq	_close
	.loc	1 678 23 is_stmt 1      ## c_posix.c:678:23
	movl	-2276(%rbp), %edi
	.loc	1 678 17 is_stmt 0      ## c_posix.c:678:17
	callq	_close
Ltmp227:
LBB0_114:                               ##   in Loop: Header=BB0_11 Depth=1
	.loc	1 321 25 is_stmt 1      ## c_posix.c:321:25
	leaq	L_.str.28(%rip), %r13
	jmp	LBB0_115
Ltmp228:
LBB0_106:                               ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 652 25                ## c_posix.c:652:25
	movl	_foreground(%rip), %edi
Ltmp229:
	##DEBUG_VALUE: main:status <- undef
	xorl	%edx, %edx
	leaq	-2404(%rbp), %rsi
	.loc	1 652 17 is_stmt 0      ## c_posix.c:652:17
	callq	_waitpid
Ltmp230:
	##DEBUG_VALUE: main:time_end <- undef
	xorl	%esi, %esi
	leaq	-2440(%rbp), %rdi
	.loc	1 655 17 is_stmt 1      ## c_posix.c:655:17
	callq	_gettimeofday
	.loc	1 656 34                ## c_posix.c:656:34
	movq	-2440(%rbp), %rax
	.loc	1 656 41 is_stmt 0      ## c_posix.c:656:41
	subq	-2424(%rbp), %rax
	.loc	1 656 62                ## c_posix.c:656:62
	imulq	$1000000, %rax, %rax    ## imm = 0xF4240
	.loc	1 657 24 is_stmt 1      ## c_posix.c:657:24
	movslq	-2432(%rbp), %rcx
	.loc	1 656 72                ## c_posix.c:656:72
	addq	%rax, %rcx
	.loc	1 657 43                ## c_posix.c:657:43
	movslq	-2416(%rbp), %rax
	.loc	1 657 41 is_stmt 0      ## c_posix.c:657:41
	subq	%rax, %rcx
Ltmp231:
	##DEBUG_VALUE: main:time <- %RCX
	.loc	1 658 62 is_stmt 1      ## c_posix.c:658:62
	movq	%rcx, %rax
	movabsq	$2361183241434822607, %rdx ## imm = 0x20C49BA5E353F7CF
	imulq	%rdx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$7, %rdx
	addq	%rax, %rdx
	.loc	1 658 75 is_stmt 0      ## c_posix.c:658:75
	imulq	$1000, %rdx, %rax       ## imm = 0x3E8
	subq	%rax, %rcx
Ltmp232:
	xorl	%eax, %eax
	.loc	1 658 17                ## c_posix.c:658:17
	leaq	L_.str.26(%rip), %rdi
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	callq	_printf
	.loc	1 660 21 is_stmt 1      ## c_posix.c:660:21
	cmpl	$1, _isSignal(%rip)
Ltmp233:
	.loc	1 321 25                ## c_posix.c:321:25
	leaq	L_.str.28(%rip), %r13
	jne	LBB0_115
Ltmp234:
## BB#107:                              ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:status <- undef
	##DEBUG_VALUE: main:time_end <- undef
	##DEBUG_VALUE: main:my_sig <- undef
	.loc	1 662 29                ## c_posix.c:662:29
	movl	$2, %edi
Ltmp235:
	xorl	%edx, %edx
	leaq	-2444(%rbp), %rsi
	callq	_sigprocmask
Ltmp236:
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 0
	.loc	1 672 21                ## c_posix.c:672:21
	movl	$20, -192(%rbp)
	jmp	LBB0_108
	.align	4, 0x90
LBB0_111:                               ##   in Loop: Header=BB0_108 Depth=2
Ltmp237:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:my_sig <- undef
	##DEBUG_VALUE: main:status <- undef
	##DEBUG_VALUE: main:time_end <- undef
	##DEBUG_VALUE: a <- 0
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 1
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	xorl	%eax, %eax
	.loc	1 321 25                ## c_posix.c:321:25
Ltmp238:
	movq	%r13, %rdi
Ltmp239:
	movl	%ecx, %esi
	callq	_printf
Ltmp240:
LBB0_108:                               ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	##DEBUG_VALUE: a <- 1
	.loc	1 308 29                ## c_posix.c:308:29
	movl	$-1, %edi
	movl	$1, %edx
Ltmp241:
	.loc	1 308 29 is_stmt 0      ## c_posix.c:308:29
	movq	%r12, %rsi
	callq	_waitpid
	movl	%eax, %ecx
Ltmp242:
	##DEBUG_VALUE: pid_my1 <- %ECX
	.loc	1 313 17 is_stmt 1      ## c_posix.c:313:17
	testl	%ecx, %ecx
	jle	LBB0_115
Ltmp243:
## BB#109:                              ## %.lr.ph26
                                        ##   in Loop: Header=BB0_108 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:my_sig <- undef
	##DEBUG_VALUE: main:status <- undef
	##DEBUG_VALUE: main:time_end <- undef
	##DEBUG_VALUE: a <- 0
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 1
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	.loc	1 315 21                ## c_posix.c:315:21
	cmpl	_foreground(%rip), %ecx
	je	LBB0_108
Ltmp244:
## BB#110:                              ##   in Loop: Header=BB0_108 Depth=2
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:my_sig <- undef
	##DEBUG_VALUE: main:status <- undef
	##DEBUG_VALUE: main:time_end <- undef
	##DEBUG_VALUE: a <- 0
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 1
	##DEBUG_VALUE: Janitor:status <- [%R12+0]
	.loc	1 319 48                ## c_posix.c:319:48
	movl	-192(%rbp), %eax
	.loc	1 319 25 is_stmt 0      ## c_posix.c:319:25
	andl	$127, %eax
	cmpl	$127, %eax
	je	LBB0_108
	jmp	LBB0_111
Ltmp245:
LBB0_115:                               ##   in Loop: Header=BB0_11 Depth=1
	.loc	1 117 25 is_stmt 1      ## c_posix.c:117:25
	leaq	L_.str.46(%rip), %r14
	.loc	1 117 9 is_stmt 0       ## c_posix.c:117:9
	leaq	L_.str.45(%rip), %r15
	jmp	LBB0_116
Ltmp246:
LBB0_68:                                ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 592 21 is_stmt 1      ## c_posix.c:592:21
	leaq	L_.str.25(%rip), %rdi
Ltmp247:
	callq	_perror
	jmp	LBB0_69
Ltmp248:
LBB0_31:                                ##   in Loop: Header=BB0_11 Depth=1
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argv <- [%RBP+-2528]
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 496 21                ## c_posix.c:496:21
	leaq	L_.str.14(%rip), %rdi
Ltmp249:
LBB0_34:                                ##   in Loop: Header=BB0_11 Depth=1
	.loc	1 506 21                ## c_posix.c:506:21
	callq	_perror
	jmp	LBB0_35
Ltmp250:
LBB0_117:                               ## %.loopexit
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	cmpq	-48(%rbp), %rax
	jne	LBB0_124
Ltmp251:
## BB#118:                              ## %.loopexit
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	.loc	1 686 5                 ## c_posix.c:686:5
	xorl	%eax, %eax
	addq	$2520, %rsp             ## imm = 0x9D8
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
Ltmp252:
LBB0_122:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 1
	.loc	1 158 17                ## c_posix.c:158:17
	leaq	L_.str.39(%rip), %rdi
Ltmp253:
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp254:
LBB0_86:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: i <- 1
	.loc	1 160 17                ## c_posix.c:160:17
	leaq	L_.str.40(%rip), %rdi
Ltmp255:
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp256:
LBB0_124:                               ## %.loopexit
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	callq	___stack_chk_fail
Ltmp257:
LBB0_36:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	movl	-2532(%rbp), %r15d      ## 4-byte Reload
	.loc	1 105 17                ## c_posix.c:105:17
Ltmp258:
	movq	___stderrp@GOTPCREL(%rip), %r13
Ltmp259:
	.loc	1 520 26                ## c_posix.c:520:26
	leaq	L_.str.17(%rip), %rdi
Ltmp260:
	callq	_getenv
Ltmp261:
	##DEBUG_VALUE: main:pagerValue <- %RAX
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:pagerValue <- %RAX
	leaq	-2336(%rbp), %rbx
	.loc	1 521 17                ## c_posix.c:521:17
	testq	%rax, %rax
	jne	LBB0_40
Ltmp262:
## BB#37:
	.loc	1 523 21                ## c_posix.c:523:21
	testl	%r15d, %r15d
	jne	LBB0_39
## BB#38:
	.loc	1 525 34                ## c_posix.c:525:34
Ltmp263:
	leaq	L_.str.3(%rip), %rax
	jmp	LBB0_40
Ltmp264:
LBB0_81:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	.loc	1 168 9                 ## c_posix.c:168:9
	leaq	L_.str.41(%rip), %rdi
Ltmp265:
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp266:
LBB0_123:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 1
	##DEBUG_VALUE: main:isBackground <- 1
	##DEBUG_VALUE: main:built_in_command <- 0
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	##DEBUG_VALUE: exec_arguments:argn <- 0
	.loc	1 88 5                  ## c_posix.c:88:5
	leaq	L___func__.exec_pipeline(%rip), %rdi
Ltmp267:
	leaq	L_.str.42(%rip), %rsi
	leaq	L_.str.53(%rip), %rcx
	movl	$88, %edx
	callq	___assert_rtn
Ltmp268:
LBB0_39:
	.loc	1 529 34                ## c_posix.c:529:34
	leaq	L_.str.18(%rip), %rax
Ltmp269:
LBB0_40:
	.loc	1 534 30                ## c_posix.c:534:30
	movq	%rax, -2336(%rbp)
Ltmp270:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	.loc	1 550 31                ## c_posix.c:550:31
	movl	$1, %edi
Ltmp271:
	callq	_malloc
Ltmp272:
	##DEBUG_VALUE: main:tmp <- %RAX
	.loc	1 551 24                ## c_posix.c:551:24
	movb	$0, (%rax)
	.loc	1 556 25                ## c_posix.c:556:25
	leaq	L_.str.23(%rip), %rcx
	movd	%rcx, %xmm0
	leaq	L_.str.22(%rip), %rcx
	movd	%rcx, %xmm1
	punpcklqdq	%xmm0, %xmm1    ## xmm1 = xmm1[0],xmm0[0]
	movdqa	%xmm1, -2368(%rbp)
	.loc	1 558 25                ## c_posix.c:558:25
	movq	%rax, -2352(%rbp)
	.loc	1 559 25                ## c_posix.c:559:25
	movq	$0, -2344(%rbp)
	leaq	-2304(%rbp), %rax
Ltmp273:
	.loc	1 560 30                ## c_posix.c:560:30
	movq	%rax, -2400(%rbp)
	leaq	-2368(%rbp), %rax
	.loc	1 561 30                ## c_posix.c:561:30
	movq	%rax, -2392(%rbp)
	leaq	-2320(%rbp), %rax
	.loc	1 562 30                ## c_posix.c:562:30
	movq	%rax, -2384(%rbp)
	.loc	1 563 30                ## c_posix.c:563:30
	movq	%rbx, -2376(%rbp)
Ltmp274:
	##DEBUG_VALUE: fork_pipes:i <- 0
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:n <- 4
	leaq	-192(%rbp), %rdi
	.loc	1 277 13                ## c_posix.c:277:13
Ltmp275:
	callq	_pipe
Ltmp276:
	.loc	1 277 13 is_stmt 0      ## c_posix.c:277:13
	cmpl	$-1, %eax
	je	LBB0_119
## BB#41:
Ltmp277:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 282 24 is_stmt 1      ## c_posix.c:282:24
	movl	-188(%rbp), %r14d
	.loc	1 243 16                ## c_posix.c:243:16
Ltmp278:
	callq	_fork
Ltmp279:
	##DEBUG_VALUE: spawn_proc:pid <- %EAX
	.loc	1 243 24 is_stmt 0      ## c_posix.c:243:24
	testl	%eax, %eax
	jne	LBB0_51
Ltmp280:
## BB#42:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	leaq	-2400(%rbp), %r12
Ltmp281:
LBB0_47:                                ## %.thread.i
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 251 17 is_stmt 1      ## c_posix.c:251:17
	cmpl	$1, %r14d
	je	LBB0_50
Ltmp282:
## BB#48:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 253 17                ## c_posix.c:253:17
	movl	$1, %esi
	movl	%r14d, %edi
Ltmp283:
	callq	_dup2
Ltmp284:
	.loc	1 253 17 is_stmt 0      ## c_posix.c:253:17
	testl	%eax, %eax
	jns	LBB0_49
## BB#120:
Ltmp285:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 254 69 is_stmt 1      ## c_posix.c:254:69
	movq	(%r12), %rax
	.loc	1 254 64 is_stmt 0      ## c_posix.c:254:64
	movq	(%rax), %rsi
	.loc	1 254 17                ## c_posix.c:254:17
	leaq	L_.str.34(%rip), %rdi
Ltmp286:
	xorl	%eax, %eax
	callq	_err_syserr
Ltmp287:
LBB0_51:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	js	LBB0_121
Ltmp288:
## BB#52:                               ## %spawn_proc.exit.i
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 283 15 is_stmt 1      ## c_posix.c:283:15
	movl	-188(%rbp), %edi
Ltmp289:
	.loc	1 283 9 is_stmt 0       ## c_posix.c:283:9
	callq	_close
	.loc	1 284 14 is_stmt 1      ## c_posix.c:284:14
	movl	-192(%rbp), %r15d
Ltmp290:
	##DEBUG_VALUE: fork_pipes:i <- 1
	##DEBUG_VALUE: fork_pipes:in <- %R15D
	leaq	-192(%rbp), %rdi
	.loc	1 277 13                ## c_posix.c:277:13
Ltmp291:
	callq	_pipe
	.loc	1 277 22 is_stmt 0      ## c_posix.c:277:22
	cmpl	$-1, %eax
	je	LBB0_119
Ltmp292:
## BB#53:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- %R15D
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 282 24 is_stmt 1      ## c_posix.c:282:24
	movl	-188(%rbp), %r14d
	.loc	1 243 16                ## c_posix.c:243:16
Ltmp293:
	callq	_fork
	movl	$1, %ecx
	.loc	1 243 24 is_stmt 0      ## c_posix.c:243:24
	testl	%eax, %eax
	je	LBB0_43
Ltmp294:
## BB#54:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	js	LBB0_121
Ltmp295:
## BB#55:                               ## %spawn_proc.exit.1.i
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 283 15 is_stmt 1      ## c_posix.c:283:15
	movl	-188(%rbp), %edi
Ltmp296:
	.loc	1 283 9 is_stmt 0       ## c_posix.c:283:9
	callq	_close
	.loc	1 284 14 is_stmt 1      ## c_posix.c:284:14
	movl	-192(%rbp), %r15d
	leaq	-192(%rbp), %rdi
	.loc	1 277 13                ## c_posix.c:277:13
Ltmp297:
	callq	_pipe
	.loc	1 277 22 is_stmt 0      ## c_posix.c:277:22
	cmpl	$-1, %eax
	jne	LBB0_56
LBB0_119:
Ltmp298:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 279 13 is_stmt 1      ## c_posix.c:279:13
	leaq	L_.str.29(%rip), %rdi
Ltmp299:
	xorl	%eax, %eax
	callq	_err_syserr
Ltmp300:
LBB0_49:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 255 13                ## c_posix.c:255:13
	movl	%r14d, %edi
Ltmp301:
	callq	_close
Ltmp302:
LBB0_50:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 257 17                ## c_posix.c:257:17
	movq	(%r13), %rbx
	.loc	1 257 52 is_stmt 0      ## c_posix.c:257:52
	callq	_getpid
	movl	%eax, %edx
	.loc	1 257 67                ## c_posix.c:257:67
	movq	(%r12), %rax
	.loc	1 257 62                ## c_posix.c:257:62
	movq	(%rax), %rcx
	.loc	1 257 9                 ## c_posix.c:257:9
	leaq	L_.str.31(%rip), %rsi
	xorl	%eax, %eax
	movq	%rbx, %rdi
Ltmp303:
	callq	_fprintf
	.loc	1 258 21 is_stmt 1      ## c_posix.c:258:21
	movq	(%r12), %rsi
	.loc	1 258 16 is_stmt 0      ## c_posix.c:258:16
	movq	(%rsi), %rdi
	.loc	1 258 9                 ## c_posix.c:258:9
	callq	_execvp
	.loc	1 259 51 is_stmt 1      ## c_posix.c:259:51
	movq	(%r12), %rax
	.loc	1 259 46 is_stmt 0      ## c_posix.c:259:46
	movq	(%rax), %rsi
Ltmp304:
LBB0_62:
	.loc	1 292 5 is_stmt 1       ## c_posix.c:292:5
	leaq	L_.str.32(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_syserr
LBB0_56:
Ltmp305:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 282 24                ## c_posix.c:282:24
	movl	-188(%rbp), %r14d
	.loc	1 243 16                ## c_posix.c:243:16
Ltmp306:
	callq	_fork
	movl	$2, %ecx
	.loc	1 243 24 is_stmt 0      ## c_posix.c:243:24
	testl	%eax, %eax
	jne	LBB0_57
Ltmp307:
LBB0_43:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 282 35 is_stmt 1      ## c_posix.c:282:35
	leaq	-2400(%rbp,%rcx,8), %r12
	.loc	1 245 16                ## c_posix.c:245:16
Ltmp308:
	testl	%r15d, %r15d
	je	LBB0_47
Ltmp309:
## BB#44:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	xorl	%esi, %esi
	.loc	1 247 17                ## c_posix.c:247:17
Ltmp310:
	movl	%r15d, %edi
Ltmp311:
	callq	_dup2
Ltmp312:
	.loc	1 247 17 is_stmt 0      ## c_posix.c:247:17
	testl	%eax, %eax
	jns	LBB0_46
## BB#45:
Ltmp313:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 248 68 is_stmt 1      ## c_posix.c:248:68
	movq	(%r12), %rax
	.loc	1 248 63 is_stmt 0      ## c_posix.c:248:63
	movq	(%rax), %rsi
Ltmp314:
LBB0_60:
	.loc	1 288 9 is_stmt 1       ## c_posix.c:288:9
	leaq	L_.str.30(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_syserr
Ltmp315:
LBB0_46:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 249 13                ## c_posix.c:249:13
	movl	%r15d, %edi
Ltmp316:
	callq	_close
	jmp	LBB0_47
Ltmp317:
LBB0_57:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	jns	LBB0_58
Ltmp318:
LBB0_121:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 263 9                 ## c_posix.c:263:9
	leaq	L_.str.35(%rip), %rdi
Ltmp319:
	xorl	%eax, %eax
	callq	_err_syserr
Ltmp320:
LBB0_58:                                ## %spawn_proc.exit.2.i
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 283 15                ## c_posix.c:283:15
	movl	-188(%rbp), %edi
Ltmp321:
	.loc	1 283 9 is_stmt 0       ## c_posix.c:283:9
	callq	_close
	.loc	1 284 14 is_stmt 1      ## c_posix.c:284:14
	movl	-192(%rbp), %edi
	xorl	%esi, %esi
Ltmp322:
	.loc	1 286 9                 ## c_posix.c:286:9
	callq	_dup2
	.loc	1 286 21 is_stmt 0      ## c_posix.c:286:21
	testl	%eax, %eax
Ltmp323:
	.loc	1 286 9                 ## c_posix.c:286:9
	jns	LBB0_61
## BB#59:
Ltmp324:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 288 55 is_stmt 1      ## c_posix.c:288:55
	movq	-2336(%rbp), %rsi
	jmp	LBB0_60
Ltmp325:
LBB0_61:
	##DEBUG_VALUE: main:argc <- %EDI
	##DEBUG_VALUE: main:argc2 <- 0
	##DEBUG_VALUE: main:i <- 0
	##DEBUG_VALUE: main:isBackground <- 0
	##DEBUG_VALUE: main:built_in_command <- 1
	##DEBUG_VALUE: main:status <- 0
	##DEBUG_VALUE: main:max <- 80
	##DEBUG_VALUE: main:pos <- 0
	##DEBUG_VALUE: main:len <- 1
	##DEBUG_VALUE: main:breakloop <- 0
	##DEBUG_VALUE: main:pid_temp <- 0
	##DEBUG_VALUE: main:ret <- 1
	##DEBUG_VALUE: main:k <- 1
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 290 13                ## c_posix.c:290:13
	movq	(%r13), %r14
	.loc	1 290 48 is_stmt 0      ## c_posix.c:290:48
	callq	_getpid
	movl	%eax, %edx
	.loc	1 290 58                ## c_posix.c:290:58
	movq	-2336(%rbp), %rcx
	.loc	1 290 5                 ## c_posix.c:290:5
	leaq	L_.str.31(%rip), %rsi
	xorl	%eax, %eax
	movq	%r14, %rdi
Ltmp326:
	callq	_fprintf
	.loc	1 291 12 is_stmt 1      ## c_posix.c:291:12
	movq	-2336(%rbp), %rdi
	.loc	1 291 5 is_stmt 0       ## c_posix.c:291:5
	movq	%rbx, %rsi
	callq	_execvp
	.loc	1 292 42 is_stmt 1      ## c_posix.c:292:42
	movq	-2336(%rbp), %rsi
	jmp	LBB0_62
Ltmp327:
Lfunc_end0:
	.cfi_endproc
	.file	5 "/usr/include/sys/_types" "_dev_t.h"
	.file	6 "/usr/include/sys" "stat.h"
	.file	7 "/usr/include/sys/_types" "_mode_t.h"
	.file	8 "/usr/include/sys/_types" "_nlink_t.h"
	.file	9 "/usr/include/sys/_types" "_uid_t.h"
	.file	10 "/usr/include/sys/_types" "_gid_t.h"
	.file	11 "/usr/include/sys/_types" "_time_t.h"
	.file	12 "/usr/include/sys/_types" "_off_t.h"
	.file	13 "/usr/include/sys/_types" "_blkcnt_t.h"
	.file	14 "/usr/include/sys/_types" "_blksize_t.h"

	.align	4, 0x90
_sighandler:                            ## @sighandler
Lfunc_begin1:
	.loc	1 359 0                 ## c_posix.c:359:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp328:
	.cfi_def_cfa_offset 16
Ltmp329:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp330:
	.cfi_def_cfa_register %rbp
	##DEBUG_VALUE: sighandler:signo <- %EDI
	##DEBUG_VALUE: sighandler:si <- %RSI
	##DEBUG_VALUE: sighandler:vp <- %RDX
	.loc	1 361 20 prologue_end   ## c_posix.c:361:20
Ltmp331:
	leaq	L_.str.27(%rip), %rsi
	movl	$2, %edi
	movl	$16, %edx
	popq	%rbp
	jmp	_write                  ## TAILCALL
Ltmp332:
Lfunc_end1:
	.cfi_endproc

	.align	4, 0x90
_err_syserr:                            ## @err_syserr
Lfunc_begin2:
	.loc	1 220 0                 ## c_posix.c:220:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp333:
	.cfi_def_cfa_offset 16
Ltmp334:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp335:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	subq	$200, %rsp
Ltmp336:
	.cfi_offset %rbx, -40
Ltmp337:
	.cfi_offset %r14, -32
Ltmp338:
	.cfi_offset %r15, -24
	##DEBUG_VALUE: err_syserr:fmt <- %RDI
	movq	%rdi, %r14
Ltmp339:
	##DEBUG_VALUE: err_syserr:fmt <- %R14
	testb	%al, %al
	je	LBB2_2
Ltmp340:
## BB#1:
	##DEBUG_VALUE: err_syserr:fmt <- %R14
	movaps	%xmm0, -176(%rbp)
	movaps	%xmm1, -160(%rbp)
	movaps	%xmm2, -144(%rbp)
	movaps	%xmm3, -128(%rbp)
	movaps	%xmm4, -112(%rbp)
	movaps	%xmm5, -96(%rbp)
	movaps	%xmm6, -80(%rbp)
	movaps	%xmm7, -64(%rbp)
Ltmp341:
LBB2_2:
	##DEBUG_VALUE: err_syserr:fmt <- %R14
	movq	%r9, -184(%rbp)
	movq	%r8, -192(%rbp)
	movq	%rcx, -200(%rbp)
	movq	%rdx, -208(%rbp)
	movq	%rsi, -216(%rbp)
	.loc	1 221 18 prologue_end   ## c_posix.c:221:18
Ltmp342:
	callq	___error
	movl	(%rax), %ebx
Ltmp343:
	##DEBUG_VALUE: err_syserr:errnum <- %EBX
	leaq	-224(%rbp), %rax
	.loc	1 223 5                 ## c_posix.c:223:5
	movq	%rax, -32(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -40(%rbp)
	movl	$48, -44(%rbp)
	movl	$8, -48(%rbp)
	.loc	1 224 14                ## c_posix.c:224:14
	movq	___stderrp@GOTPCREL(%rip), %r15
	movq	(%r15), %rdi
	leaq	-48(%rbp), %rdx
Ltmp344:
	##DEBUG_VALUE: err_syserr:args <- [%RDX+0]
	.loc	1 224 5 is_stmt 0       ## c_posix.c:224:5
	movq	%r14, %rsi
Ltmp345:
	##DEBUG_VALUE: err_syserr:fmt <- %RSI
	callq	_vfprintf
	.loc	1 226 16 is_stmt 1      ## c_posix.c:226:16
Ltmp346:
	testl	%ebx, %ebx
	je	LBB2_4
Ltmp347:
## BB#3:
	##DEBUG_VALUE: err_syserr:errnum <- %EBX
	.loc	1 227 17                ## c_posix.c:227:17
	movq	(%r15), %r14
	.loc	1 227 47 is_stmt 0      ## c_posix.c:227:47
	movl	%ebx, %edi
	callq	_strerror
	movq	%rax, %rcx
	.loc	1 227 9                 ## c_posix.c:227:9
	leaq	L_.str.33(%rip), %rsi
	xorl	%eax, %eax
	movq	%r14, %rdi
	movl	%ebx, %edx
	callq	_fprintf
Ltmp348:
LBB2_4:
	.loc	1 228 5 is_stmt 1       ## c_posix.c:228:5
	movl	$1, %edi
	callq	_exit
Ltmp349:
Lfunc_end2:
	.cfi_endproc

	.align	4, 0x90
_err_sysexit:                           ## @err_sysexit
Lfunc_begin3:
	.loc	1 203 0                 ## c_posix.c:203:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp350:
	.cfi_def_cfa_offset 16
Ltmp351:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp352:
	.cfi_def_cfa_register %rbp
	subq	$208, %rsp
	##DEBUG_VALUE: err_sysexit:fmt <- %RDI
	testb	%al, %al
	je	LBB3_2
Ltmp353:
## BB#1:
	##DEBUG_VALUE: err_sysexit:fmt <- %RDI
	movaps	%xmm0, -160(%rbp)
	movaps	%xmm1, -144(%rbp)
	movaps	%xmm2, -128(%rbp)
	movaps	%xmm3, -112(%rbp)
	movaps	%xmm4, -96(%rbp)
	movaps	%xmm5, -80(%rbp)
	movaps	%xmm6, -64(%rbp)
	movaps	%xmm7, -48(%rbp)
Ltmp354:
LBB3_2:
	##DEBUG_VALUE: err_sysexit:fmt <- %RDI
	movq	%r9, -168(%rbp)
	movq	%r8, -176(%rbp)
	movq	%rcx, -184(%rbp)
	movq	%rdx, -192(%rbp)
	movq	%rsi, -200(%rbp)
	leaq	-208(%rbp), %rax
	.loc	1 205 5 prologue_end    ## c_posix.c:205:5
Ltmp355:
	movq	%rax, -16(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$48, -28(%rbp)
	movl	$8, -32(%rbp)
	leaq	-32(%rbp), %rsi
Ltmp356:
	##DEBUG_VALUE: err_sysexit:args <- [%RSI+0]
	.loc	1 206 5                 ## c_posix.c:206:5
	callq	_err_vsyswarn
	.loc	1 208 5                 ## c_posix.c:208:5
	movl	$1, %edi
Ltmp357:
	callq	_exit
Ltmp358:
Lfunc_end3:
	.cfi_endproc

	.align	4, 0x90
_err_vsyswarn:                          ## @err_vsyswarn
Lfunc_begin4:
	.loc	1 185 0                 ## c_posix.c:185:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp359:
	.cfi_def_cfa_offset 16
Ltmp360:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp361:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	pushq	%rax
Ltmp362:
	.cfi_offset %rbx, -56
Ltmp363:
	.cfi_offset %r12, -48
Ltmp364:
	.cfi_offset %r13, -40
Ltmp365:
	.cfi_offset %r14, -32
Ltmp366:
	.cfi_offset %r15, -24
	##DEBUG_VALUE: err_vsyswarn:fmt <- %RDI
	##DEBUG_VALUE: err_vsyswarn:args <- %RSI
	movq	%rsi, %r14
Ltmp367:
	##DEBUG_VALUE: err_vsyswarn:args <- %R14
	movq	%rdi, %r15
Ltmp368:
	##DEBUG_VALUE: err_vsyswarn:fmt <- %R15
	.loc	1 186 18 prologue_end   ## c_posix.c:186:18
	callq	___error
	movl	(%rax), %r12d
Ltmp369:
	##DEBUG_VALUE: err_vsyswarn:errnum <- %R12D
	.loc	1 187 13                ## c_posix.c:187:13
	movq	___stderrp@GOTPCREL(%rip), %rax
	movq	(%rax), %r13
	.loc	1 187 32 is_stmt 0      ## c_posix.c:187:32
	movq	_arg0(%rip), %rbx
	.loc	1 187 43                ## c_posix.c:187:43
	callq	_getpid
	movl	%eax, %ecx
	.loc	1 187 5                 ## c_posix.c:187:5
	leaq	L_.str.48(%rip), %rsi
	xorl	%eax, %eax
	movq	%r13, %rdi
	.loc	1 187 13                ## c_posix.c:187:13
	movq	___stderrp@GOTPCREL(%rip), %r13
	.loc	1 187 5                 ## c_posix.c:187:5
	movq	%rbx, %rdx
	callq	_fprintf
	.loc	1 188 14 is_stmt 1      ## c_posix.c:188:14
	movq	(%r13), %rdi
	.loc	1 188 5 is_stmt 0       ## c_posix.c:188:5
	movq	%r15, %rsi
Ltmp370:
	##DEBUG_VALUE: err_vsyswarn:fmt <- %RSI
	movq	%r14, %rdx
Ltmp371:
	##DEBUG_VALUE: err_vsyswarn:args <- %RDX
	callq	_vfprintf
	.loc	1 189 16 is_stmt 1      ## c_posix.c:189:16
Ltmp372:
	testl	%r12d, %r12d
	je	LBB4_2
Ltmp373:
## BB#1:
	##DEBUG_VALUE: err_vsyswarn:errnum <- %R12D
	.loc	1 190 17                ## c_posix.c:190:17
	movq	(%r13), %rbx
	.loc	1 190 46 is_stmt 0      ## c_posix.c:190:46
	movl	%r12d, %edi
	callq	_strerror
	movq	%rax, %rcx
	.loc	1 190 9                 ## c_posix.c:190:9
	leaq	L_.str.49(%rip), %rsi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	movl	%r12d, %edx
	callq	_fprintf
Ltmp374:
LBB4_2:
	.loc	1 191 16 is_stmt 1      ## c_posix.c:191:16
	movq	(%r13), %rsi
	.loc	1 191 5 is_stmt 0       ## c_posix.c:191:5
	movl	$10, %edi
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	jmp	_putc                   ## TAILCALL
Ltmp375:
Lfunc_end4:
	.cfi_endproc

	.align	4, 0x90
_err_syswarn:                           ## @err_syswarn
Lfunc_begin5:
	.loc	1 195 0 is_stmt 1       ## c_posix.c:195:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp376:
	.cfi_def_cfa_offset 16
Ltmp377:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp378:
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$216, %rsp
Ltmp379:
	.cfi_offset %rbx, -24
	testb	%al, %al
	je	LBB5_2
## BB#1:
	movaps	%xmm0, -176(%rbp)
	movaps	%xmm1, -160(%rbp)
	movaps	%xmm2, -144(%rbp)
	movaps	%xmm3, -128(%rbp)
	movaps	%xmm4, -112(%rbp)
	movaps	%xmm5, -96(%rbp)
	movaps	%xmm6, -80(%rbp)
	movaps	%xmm7, -64(%rbp)
LBB5_2:
	movq	%r9, -184(%rbp)
	movq	%r8, -192(%rbp)
	movq	%rcx, -200(%rbp)
	movq	%rdx, -208(%rbp)
	movq	%rsi, -216(%rbp)
	movq	___stack_chk_guard@GOTPCREL(%rip), %rbx
	movq	(%rbx), %rbx
	movq	%rbx, -16(%rbp)
	leaq	-224(%rbp), %rax
	.loc	1 197 5 prologue_end    ## c_posix.c:197:5
Ltmp380:
	movq	%rax, -32(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -40(%rbp)
	movl	$48, -44(%rbp)
	movl	$8, -48(%rbp)
	.loc	1 198 5                 ## c_posix.c:198:5
	leaq	L_.str.54(%rip), %rdi
	leaq	-48(%rbp), %rsi
Ltmp381:
	##DEBUG_VALUE: err_syswarn:args <- [%RSI+0]
	callq	_err_vsyswarn
	cmpq	-16(%rbp), %rbx
	jne	LBB5_4
Ltmp382:
## BB#3:
	.loc	1 200 1                 ## c_posix.c:200:1
	addq	$216, %rsp
	popq	%rbx
	popq	%rbp
	retq
Ltmp383:
LBB5_4:
	callq	___stack_chk_fail
Lfunc_end5:
	.cfi_endproc

	.align	4, 0x90
_exec_nth_command:                      ## @exec_nth_command
Lfunc_begin6:
	.loc	1 48 0                  ## c_posix.c:48:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp384:
	.cfi_def_cfa_offset 16
Ltmp385:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp386:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	pushq	%rax
Ltmp387:
	.cfi_offset %rbx, -40
Ltmp388:
	.cfi_offset %r14, -32
Ltmp389:
	.cfi_offset %r15, -24
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EDI
	##DEBUG_VALUE: exec_nth_command:cmds <- %RSI
	movq	%rsi, %r14
Ltmp390:
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	movl	%edi, %ebx
Ltmp391:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	.loc	1 49 5 prologue_end     ## c_posix.c:49:5
	testl	%ebx, %ebx
	jg	LBB6_1
Ltmp392:
## BB#8:
	leaq	L___func__.exec_nth_command(%rip), %rdi
	leaq	L_.str.42(%rip), %rsi
	leaq	L_.str.53(%rip), %rcx
	movl	$49, %edx
	callq	___assert_rtn
LBB6_1:
Ltmp393:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	.loc	1 50 9                  ## c_posix.c:50:9
	cmpl	$2, %ebx
	jl	LBB6_7
Ltmp394:
## BB#2:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	leaq	-32(%rbp), %rdi
Ltmp395:
	##DEBUG_VALUE: exec_pipe_command:output <- %RDI
	##DEBUG_VALUE: input <- [%RDI+0]
	.loc	1 54 13                 ## c_posix.c:54:13
	callq	_pipe
	.loc	1 54 25 is_stmt 0       ## c_posix.c:54:25
	testl	%eax, %eax
Ltmp396:
	.loc	1 54 13                 ## c_posix.c:54:13
	jne	LBB6_9
Ltmp397:
## BB#3:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	.loc	1 56 20 is_stmt 1       ## c_posix.c:56:20
	callq	_fork
Ltmp398:
	##DEBUG_VALUE: pid <- %EAX
	.loc	1 56 13 is_stmt 0       ## c_posix.c:56:13
	testl	%eax, %eax
	jns	LBB6_4
Ltmp399:
## BB#10:
	.loc	1 57 13 is_stmt 1       ## c_posix.c:57:13
	leaq	L_.str.54(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp400:
LBB6_9:
	.loc	1 55 13                 ## c_posix.c:55:13
	leaq	L_.str.55(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp401:
LBB6_4:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	jne	LBB6_6
Ltmp402:
## BB#5:                                ## %exec_pipe_command.exit
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	.loc	1 61 37                 ## c_posix.c:61:37
	leal	-1(%rbx), %r15d
Ltmp403:
	##DEBUG_VALUE: exec_pipe_command:ncmds <- %R15D
	.loc	1 78 10                 ## c_posix.c:78:10
	movl	-28(%rbp), %edi
	.loc	1 78 5 is_stmt 0        ## c_posix.c:78:5
	movl	$1, %esi
	callq	_dup2
	.loc	1 79 11 is_stmt 1       ## c_posix.c:79:11
	movl	-32(%rbp), %edi
	.loc	1 79 5 is_stmt 0        ## c_posix.c:79:5
	callq	_close
	.loc	1 80 11 is_stmt 1       ## c_posix.c:80:11
	movl	-28(%rbp), %edi
	.loc	1 80 5 is_stmt 0        ## c_posix.c:80:5
	callq	_close
Ltmp404:
	##DEBUG_VALUE: exec_pipe_command:cmds <- %R14
	.loc	1 81 5 is_stmt 1        ## c_posix.c:81:5
	movl	%r15d, %edi
	movq	%r14, %rsi
	callq	_exec_nth_command
Ltmp405:
LBB6_6:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	.loc	1 64 14                 ## c_posix.c:64:14
	movl	-32(%rbp), %edi
	.loc	1 64 9 is_stmt 0        ## c_posix.c:64:9
	xorl	%esi, %esi
	callq	_dup2
	.loc	1 65 15 is_stmt 1       ## c_posix.c:65:15
	movl	-32(%rbp), %edi
	.loc	1 65 9 is_stmt 0        ## c_posix.c:65:9
	callq	_close
	.loc	1 66 15 is_stmt 1       ## c_posix.c:66:15
	movl	-28(%rbp), %edi
	.loc	1 66 9 is_stmt 0        ## c_posix.c:66:9
	callq	_close
Ltmp406:
LBB6_7:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	.loc	1 68 12 is_stmt 1       ## c_posix.c:68:12
	movslq	%ebx, %rbx
Ltmp407:
	movq	-8(%r14,%rbx,8), %rsi
	movq	(%rsi), %rdi
	.loc	1 68 5 is_stmt 0        ## c_posix.c:68:5
	callq	_execvp
	.loc	1 69 38 is_stmt 1       ## c_posix.c:69:38
	movq	-8(%r14,%rbx,8), %rax
	movq	(%rax), %rsi
	.loc	1 69 5 is_stmt 0        ## c_posix.c:69:5
	leaq	L_.str.56(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp408:
Lfunc_end6:
	.cfi_endproc

	.globl	_isSignal               ## @isSignal
.zerofill __DATA,__common,_isSignal,4,2
	.section	__DATA,__data
	.globl	_foreground             ## @foreground
	.align	2
_foreground:
	.long	4294967295              ## 0xffffffff

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	" "

L_.str.1:                               ## @.str.1
	.asciz	"printenv"

	.section	__DATA,__const
	.align	4                       ## @main.printenv
l_main.printenv:
	.quad	L_.str.1
	.quad	0

	.section	__TEXT,__cstring,cstring_literals
L_.str.2:                               ## @.str.2
	.asciz	"sort"

	.section	__DATA,__const
	.align	4                       ## @main.sort
l_main.sort:
	.quad	L_.str.2
	.quad	0

	.section	__TEXT,__cstring,cstring_literals
L_.str.3:                               ## @.str.3
	.asciz	"less"

	.section	__DATA,__const
	.align	4                       ## @main.pager_cmd
l_main.pager_cmd:
	.quad	L_.str.3
	.quad	0

	.section	__TEXT,__cstring,cstring_literals
L_.str.4:                               ## @.str.4
	.asciz	"PATH"

L_.str.5:                               ## @.str.5
	.asciz	"'%s' is not set.\n"

L_.str.6:                               ## @.str.6
	.asciz	"'%s' is set to %s.\n"

L_.str.7:                               ## @.str.7
	.asciz	":"

L_.str.8:                               ## @.str.8
	.asciz	"/less"

L_.str.10:                              ## @.str.10
	.asciz	"miniShell>> "

L_.str.12:                              ## @.str.12
	.asciz	"exit"

L_.str.13:                              ## @.str.13
	.asciz	"cd"

L_.str.14:                              ## @.str.14
	.asciz	"Failed changing to homedirectory\n"

L_.str.15:                              ## @.str.15
	.asciz	"Failed changing directory\n"

L_.str.16:                              ## @.str.16
	.asciz	"unixinfo"

L_.str.17:                              ## @.str.17
	.asciz	"PAGER"

L_.str.18:                              ## @.str.18
	.asciz	"more"

L_.str.21:                              ## @.str.21
	.asciz	"|"

L_.str.22:                              ## @.str.22
	.asciz	"grep"

L_.str.23:                              ## @.str.23
	.asciz	"-E"

L_.str.25:                              ## @.str.25
	.asciz	"Failed creating pipe\n"

L_.str.26:                              ## @.str.26
	.asciz	"Execution time %ld.%03ld ms\n"

L_.str.27:                              ## @.str.27
	.asciz	"Received SIGINT\n"

L_.str.28:                              ## @.str.28
	.asciz	"\n\n\n\n%d terminated \n\n\n\n\n"

L_.str.29:                              ## @.str.29
	.asciz	"Failed creating pipe"

L_.str.30:                              ## @.str.30
	.asciz	"dup2() failed on stdin for %s: "

L_.str.31:                              ## @.str.31
	.asciz	"%d: executing %s\n"

L_.str.32:                              ## @.str.32
	.asciz	"failed to execute %s: "

L_.str.33:                              ## @.str.33
	.asciz	"(%d: %s)\n"

L_.str.34:                              ## @.str.34
	.asciz	"dup2() failed on stdout for %s: "

L_.str.35:                              ## @.str.35
	.asciz	"fork failed: "

	.section	__DATA,__data
	.align	3                       ## @arg0
_arg0:
	.quad	L_.str.36

	.section	__TEXT,__cstring,cstring_literals
L_.str.36:                              ## @.str.36
	.asciz	"<undefined>"

L_.str.37:                              ## @.str.37
	.asciz	"Entering exec_arguments"

L_.str.38:                              ## @.str.38
	.asciz	"Processing %d [%s]\n"

L_.str.39:                              ## @.str.39
	.asciz	"Syntax error: pipe before any command"

L_.str.40:                              ## @.str.40
	.asciz	"Syntax error: two pipes with no command between"

L_.str.41:                              ## @.str.41
	.asciz	"Syntax error: pipe with no command following"

L_.str.42:                              ## @.str.42
	.asciz	"c_posix.c"

L_.str.44:                              ## @.str.44
	.asciz	"%s: (%d)"

L_.str.45:                              ## @.str.45
	.asciz	" {%s}"

L_.str.46:                              ## @.str.46
	.asciz	"(null)"

L_.str.48:                              ## @.str.48
	.asciz	"%s:%d: "

L_.str.49:                              ## @.str.49
	.asciz	" (%d: %s)"

L_.str.51:                              ## @.str.51
	.asciz	"cmd [%d]"

L___func__.exec_pipeline:               ## @__func__.exec_pipeline
	.asciz	"exec_pipeline"

L_.str.53:                              ## @.str.53
	.asciz	"ncmds >= 1"

L_.str.54:                              ## @.str.54
	.asciz	"Failed to fork"

L___func__.exec_nth_command:            ## @__func__.exec_nth_command
	.asciz	"exec_nth_command"

L_.str.55:                              ## @.str.55
	.asciz	"Failed to create pipe"

L_.str.56:                              ## @.str.56
	.asciz	"Failed to exec %s"

L_.str.57:                              ## @.str.57
	.asciz	"%d: child %d status 0x%.4X\n"

L_str:                                  ## @str
	.asciz	"malloc failed!"

L_str.58:                               ## @str.58
	.asciz	"SOC"

L_str.59:                               ## @str.59
	.asciz	"EOC"

	.file	15 "/usr/include" "signal.h"
	.file	16 "/usr/include/sys" "signal.h"
	.file	17 "/usr/include/sys/_types" "_sigset_t.h"
	.file	18 "/usr/include/sys/_types" "_size_t.h"
	.file	19 "/usr/include" "pwd.h"
	.file	20 "/usr/include/sys/_types" "_timeval.h"
	.file	21 "/usr/include/sys/_types" "_va_list.h"
	.section	__DWARF,__debug_str,regular,debug
Linfo_string:
	.asciz	"Apple LLVM version 7.3.0 (clang-703.0.29)" ## string offset=0
	.asciz	"c_posix.c"             ## string offset=42
	.asciz	"/Users/jleffler/soq"   ## string offset=52
	.asciz	"isSignal"              ## string offset=72
	.asciz	"int"                   ## string offset=81
	.asciz	"foreground"            ## string offset=85
	.asciz	"pid_t"                 ## string offset=96
	.asciz	"__darwin_pid_t"        ## string offset=102
	.asciz	"__int32_t"             ## string offset=117
	.asciz	"arg0"                  ## string offset=127
	.asciz	"char"                  ## string offset=132
	.asciz	"file_exist"            ## string offset=137
	.asciz	"filename"              ## string offset=148
	.asciz	"buffer"                ## string offset=157
	.asciz	"stat"                  ## string offset=164
	.asciz	"st_dev"                ## string offset=169
	.asciz	"dev_t"                 ## string offset=176
	.asciz	"__darwin_dev_t"        ## string offset=182
	.asciz	"st_mode"               ## string offset=197
	.asciz	"mode_t"                ## string offset=205
	.asciz	"__darwin_mode_t"       ## string offset=212
	.asciz	"__uint16_t"            ## string offset=228
	.asciz	"unsigned short"        ## string offset=239
	.asciz	"st_nlink"              ## string offset=254
	.asciz	"nlink_t"               ## string offset=263
	.asciz	"st_ino"                ## string offset=271
	.asciz	"__darwin_ino64_t"      ## string offset=278
	.asciz	"__uint64_t"            ## string offset=295
	.asciz	"long long unsigned int" ## string offset=306
	.asciz	"st_uid"                ## string offset=329
	.asciz	"uid_t"                 ## string offset=336
	.asciz	"__darwin_uid_t"        ## string offset=342
	.asciz	"__uint32_t"            ## string offset=357
	.asciz	"unsigned int"          ## string offset=368
	.asciz	"st_gid"                ## string offset=381
	.asciz	"gid_t"                 ## string offset=388
	.asciz	"__darwin_gid_t"        ## string offset=394
	.asciz	"st_rdev"               ## string offset=409
	.asciz	"st_atime"              ## string offset=417
	.asciz	"time_t"                ## string offset=426
	.asciz	"__darwin_time_t"       ## string offset=433
	.asciz	"long int"              ## string offset=449
	.asciz	"st_atimensec"          ## string offset=458
	.asciz	"st_mtime"              ## string offset=471
	.asciz	"st_mtimensec"          ## string offset=480
	.asciz	"st_ctime"              ## string offset=493
	.asciz	"st_ctimensec"          ## string offset=502
	.asciz	"st_birthtime"          ## string offset=515
	.asciz	"st_birthtimensec"      ## string offset=528
	.asciz	"st_size"               ## string offset=545
	.asciz	"off_t"                 ## string offset=553
	.asciz	"__darwin_off_t"        ## string offset=559
	.asciz	"__int64_t"             ## string offset=574
	.asciz	"long long int"         ## string offset=584
	.asciz	"st_blocks"             ## string offset=598
	.asciz	"blkcnt_t"              ## string offset=608
	.asciz	"__darwin_blkcnt_t"     ## string offset=617
	.asciz	"st_blksize"            ## string offset=635
	.asciz	"blksize_t"             ## string offset=646
	.asciz	"__darwin_blksize_t"    ## string offset=656
	.asciz	"st_flags"              ## string offset=675
	.asciz	"st_gen"                ## string offset=684
	.asciz	"st_lspare"             ## string offset=691
	.asciz	"st_qspare"             ## string offset=701
	.asciz	"sizetype"              ## string offset=711
	.asciz	"Janitor"               ## string offset=720
	.asciz	"status"                ## string offset=728
	.asciz	"a"                     ## string offset=735
	.asciz	"pid_my1"               ## string offset=737
	.asciz	"dump_argv"             ## string offset=745
	.asciz	"tag"                   ## string offset=755
	.asciz	"argc"                  ## string offset=759
	.asciz	"argv"                  ## string offset=764
	.asciz	"i"                     ## string offset=769
	.asciz	"exec_arguments"        ## string offset=771
	.asciz	"argn"                  ## string offset=786
	.asciz	"cmdn"                  ## string offset=791
	.asciz	"cmdv"                  ## string offset=796
	.asciz	"args"                  ## string offset=801
	.asciz	"arg"                   ## string offset=806
	.asciz	"RemoveSpaces"          ## string offset=810
	.asciz	"source"                ## string offset=823
	.asciz	"j"                     ## string offset=830
	.asciz	"StartsWith"            ## string offset=832
	.asciz	"b"                     ## string offset=843
	.asciz	"err_setarg0"           ## string offset=845
	.asciz	"argv0"                 ## string offset=857
	.asciz	"dump_pipeline"         ## string offset=863
	.asciz	"exec_pipeline"         ## string offset=877
	.asciz	"ncmds"                 ## string offset=891
	.asciz	"cmds"                  ## string offset=897
	.asciz	"pid"                   ## string offset=902
	.asciz	"corpse_collector"      ## string offset=906
	.asciz	"parent"                ## string offset=923
	.asciz	"corpse"                ## string offset=930
	.asciz	"fork_pipes"            ## string offset=937
	.asciz	"n"                     ## string offset=948
	.asciz	"cmd"                   ## string offset=950
	.asciz	"command"               ## string offset=954
	.asciz	"fd"                    ## string offset=962
	.asciz	"in"                    ## string offset=965
	.asciz	"spawn_proc"            ## string offset=968
	.asciz	"out"                   ## string offset=979
	.asciz	"main"                  ## string offset=983
	.asciz	"sighandler"            ## string offset=988
	.asciz	"err_syserr"            ## string offset=999
	.asciz	"err_sysexit"           ## string offset=1010
	.asciz	"err_vsyswarn"          ## string offset=1022
	.asciz	"err_syswarn"           ## string offset=1035
	.asciz	"exec_pipe_command"     ## string offset=1047
	.asciz	"output"                ## string offset=1065
	.asciz	"exec_nth_command"      ## string offset=1072
	.asciz	"__sigbits"             ## string offset=1089
	.asciz	"array"                 ## string offset=1099
	.asciz	"line"                  ## string offset=1105
	.asciz	"line2"                 ## string offset=1110
	.asciz	"printenv"              ## string offset=1116
	.asciz	"sort"                  ## string offset=1125
	.asciz	"pager_cmd"             ## string offset=1130
	.asciz	"grep"                  ## string offset=1140
	.asciz	"cmd2"                  ## string offset=1145
	.asciz	"built_in_command"      ## string offset=1150
	.asciz	"isBackground"          ## string offset=1167
	.asciz	"argc2"                 ## string offset=1180
	.asciz	"breakloop"             ## string offset=1186
	.asciz	"len"                   ## string offset=1196
	.asciz	"pos"                   ## string offset=1200
	.asciz	"max"                   ## string offset=1204
	.asciz	"pid_temp"              ## string offset=1208
	.asciz	"sa"                    ## string offset=1217
	.asciz	"sigaction"             ## string offset=1220
	.asciz	"__sigaction_u"         ## string offset=1230
	.asciz	"__sa_handler"          ## string offset=1244
	.asciz	"__sa_sigaction"        ## string offset=1257
	.asciz	"__siginfo"             ## string offset=1272
	.asciz	"si_signo"              ## string offset=1282
	.asciz	"si_errno"              ## string offset=1291
	.asciz	"si_code"               ## string offset=1300
	.asciz	"si_pid"                ## string offset=1308
	.asciz	"si_uid"                ## string offset=1315
	.asciz	"si_status"             ## string offset=1322
	.asciz	"si_addr"               ## string offset=1332
	.asciz	"si_value"              ## string offset=1340
	.asciz	"sigval"                ## string offset=1349
	.asciz	"sival_int"             ## string offset=1356
	.asciz	"sival_ptr"             ## string offset=1366
	.asciz	"si_band"               ## string offset=1376
	.asciz	"__pad"                 ## string offset=1384
	.asciz	"long unsigned int"     ## string offset=1390
	.asciz	"sa_mask"               ## string offset=1408
	.asciz	"sigset_t"              ## string offset=1416
	.asciz	"__darwin_sigset_t"     ## string offset=1425
	.asciz	"sa_flags"              ## string offset=1443
	.asciz	"osa"                   ## string offset=1452
	.asciz	"pathValue"             ## string offset=1456
	.asciz	"pathValue2"            ## string offset=1466
	.asciz	"ret"                   ## string offset=1477
	.asciz	"token3"                ## string offset=1481
	.asciz	"new_str"               ## string offset=1488
	.asciz	"length"                ## string offset=1496
	.asciz	"size_t"                ## string offset=1503
	.asciz	"__darwin_size_t"       ## string offset=1510
	.asciz	"tokenstr"              ## string offset=1526
	.asciz	"pw"                    ## string offset=1535
	.asciz	"passwd"                ## string offset=1538
	.asciz	"pw_name"               ## string offset=1545
	.asciz	"pw_passwd"             ## string offset=1553
	.asciz	"pw_uid"                ## string offset=1563
	.asciz	"pw_gid"                ## string offset=1570
	.asciz	"pw_change"             ## string offset=1577
	.asciz	"pw_class"              ## string offset=1587
	.asciz	"pw_gecos"              ## string offset=1596
	.asciz	"pw_dir"                ## string offset=1605
	.asciz	"pw_shell"              ## string offset=1612
	.asciz	"pw_expire"             ## string offset=1621
	.asciz	"homedir"               ## string offset=1631
	.asciz	"time_start"            ## string offset=1639
	.asciz	"timeval"               ## string offset=1650
	.asciz	"tv_sec"                ## string offset=1658
	.asciz	"tv_usec"               ## string offset=1665
	.asciz	"__darwin_suseconds_t"  ## string offset=1673
	.asciz	"my_sig"                ## string offset=1694
	.asciz	"p"                     ## string offset=1701
	.asciz	"time_end"              ## string offset=1703
	.asciz	"time"                  ## string offset=1712
	.asciz	"pagerValue"            ## string offset=1717
	.asciz	"k"                     ## string offset=1728
	.asciz	"tmp"                   ## string offset=1730
	.asciz	"argv2"                 ## string offset=1734
	.asciz	"search"                ## string offset=1740
	.asciz	"signo"                 ## string offset=1747
	.asciz	"si"                    ## string offset=1753
	.asciz	"siginfo_t"             ## string offset=1756
	.asciz	"vp"                    ## string offset=1766
	.asciz	"return_value"          ## string offset=1769
	.asciz	"va_list"               ## string offset=1782
	.asciz	"__darwin_va_list"      ## string offset=1790
	.asciz	"__builtin_va_list"     ## string offset=1807
	.asciz	"__va_list_tag"         ## string offset=1825
	.asciz	"gp_offset"             ## string offset=1839
	.asciz	"fp_offset"             ## string offset=1849
	.asciz	"overflow_arg_area"     ## string offset=1859
	.asciz	"reg_save_area"         ## string offset=1877
	.asciz	"fmt"                   ## string offset=1891
	.asciz	"errnum"                ## string offset=1895
	.asciz	"input"                 ## string offset=1902
	.asciz	"Pipe"                  ## string offset=1908
	.asciz	"__signo"               ## string offset=1913
	.section	__DWARF,__debug_loc,regular,debug
Lsection_debug_loc:
Ldebug_loc0:
Lset0 = Lfunc_begin0-Lfunc_begin0
	.quad	Lset0
Lset1 = Ltmp15-Lfunc_begin0
	.quad	Lset1
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset2 = Ltmp17-Lfunc_begin0
	.quad	Lset2
Lset3 = Ltmp18-Lfunc_begin0
	.quad	Lset3
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset4 = Ltmp19-Lfunc_begin0
	.quad	Lset4
Lset5 = Ltmp20-Lfunc_begin0
	.quad	Lset5
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset6 = Ltmp21-Lfunc_begin0
	.quad	Lset6
Lset7 = Ltmp22-Lfunc_begin0
	.quad	Lset7
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset8 = Ltmp26-Lfunc_begin0
	.quad	Lset8
Lset9 = Ltmp28-Lfunc_begin0
	.quad	Lset9
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset10 = Ltmp31-Lfunc_begin0
	.quad	Lset10
Lset11 = Ltmp32-Lfunc_begin0
	.quad	Lset11
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset12 = Ltmp36-Lfunc_begin0
	.quad	Lset12
Lset13 = Ltmp37-Lfunc_begin0
	.quad	Lset13
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset14 = Ltmp38-Lfunc_begin0
	.quad	Lset14
Lset15 = Ltmp39-Lfunc_begin0
	.quad	Lset15
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset16 = Ltmp41-Lfunc_begin0
	.quad	Lset16
Lset17 = Ltmp43-Lfunc_begin0
	.quad	Lset17
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset18 = Ltmp46-Lfunc_begin0
	.quad	Lset18
Lset19 = Ltmp47-Lfunc_begin0
	.quad	Lset19
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset20 = Ltmp48-Lfunc_begin0
	.quad	Lset20
Lset21 = Ltmp51-Lfunc_begin0
	.quad	Lset21
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset22 = Ltmp54-Lfunc_begin0
	.quad	Lset22
Lset23 = Ltmp57-Lfunc_begin0
	.quad	Lset23
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset24 = Ltmp59-Lfunc_begin0
	.quad	Lset24
Lset25 = Ltmp62-Lfunc_begin0
	.quad	Lset25
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset26 = Ltmp66-Lfunc_begin0
	.quad	Lset26
Lset27 = Ltmp69-Lfunc_begin0
	.quad	Lset27
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset28 = Ltmp73-Lfunc_begin0
	.quad	Lset28
Lset29 = Ltmp81-Lfunc_begin0
	.quad	Lset29
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset30 = Ltmp83-Lfunc_begin0
	.quad	Lset30
Lset31 = Ltmp85-Lfunc_begin0
	.quad	Lset31
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset32 = Ltmp86-Lfunc_begin0
	.quad	Lset32
Lset33 = Ltmp87-Lfunc_begin0
	.quad	Lset33
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset34 = Ltmp89-Lfunc_begin0
	.quad	Lset34
Lset35 = Ltmp90-Lfunc_begin0
	.quad	Lset35
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset36 = Ltmp92-Lfunc_begin0
	.quad	Lset36
Lset37 = Ltmp93-Lfunc_begin0
	.quad	Lset37
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset38 = Ltmp97-Lfunc_begin0
	.quad	Lset38
Lset39 = Ltmp98-Lfunc_begin0
	.quad	Lset39
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset40 = Ltmp99-Lfunc_begin0
	.quad	Lset40
Lset41 = Ltmp100-Lfunc_begin0
	.quad	Lset41
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset42 = Ltmp105-Lfunc_begin0
	.quad	Lset42
Lset43 = Ltmp106-Lfunc_begin0
	.quad	Lset43
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset44 = Ltmp108-Lfunc_begin0
	.quad	Lset44
Lset45 = Ltmp125-Lfunc_begin0
	.quad	Lset45
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset46 = Ltmp128-Lfunc_begin0
	.quad	Lset46
Lset47 = Ltmp133-Lfunc_begin0
	.quad	Lset47
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset48 = Ltmp134-Lfunc_begin0
	.quad	Lset48
Lset49 = Ltmp136-Lfunc_begin0
	.quad	Lset49
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset50 = Ltmp137-Lfunc_begin0
	.quad	Lset50
Lset51 = Ltmp141-Lfunc_begin0
	.quad	Lset51
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset52 = Ltmp143-Lfunc_begin0
	.quad	Lset52
Lset53 = Ltmp145-Lfunc_begin0
	.quad	Lset53
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset54 = Ltmp148-Lfunc_begin0
	.quad	Lset54
Lset55 = Ltmp151-Lfunc_begin0
	.quad	Lset55
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset56 = Ltmp153-Lfunc_begin0
	.quad	Lset56
Lset57 = Ltmp154-Lfunc_begin0
	.quad	Lset57
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset58 = Ltmp156-Lfunc_begin0
	.quad	Lset58
Lset59 = Ltmp157-Lfunc_begin0
	.quad	Lset59
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset60 = Ltmp162-Lfunc_begin0
	.quad	Lset60
Lset61 = Ltmp164-Lfunc_begin0
	.quad	Lset61
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset62 = Ltmp167-Lfunc_begin0
	.quad	Lset62
Lset63 = Ltmp182-Lfunc_begin0
	.quad	Lset63
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset64 = Ltmp184-Lfunc_begin0
	.quad	Lset64
Lset65 = Ltmp186-Lfunc_begin0
	.quad	Lset65
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset66 = Ltmp189-Lfunc_begin0
	.quad	Lset66
Lset67 = Ltmp191-Lfunc_begin0
	.quad	Lset67
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset68 = Ltmp192-Lfunc_begin0
	.quad	Lset68
Lset69 = Ltmp193-Lfunc_begin0
	.quad	Lset69
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset70 = Ltmp195-Lfunc_begin0
	.quad	Lset70
Lset71 = Ltmp196-Lfunc_begin0
	.quad	Lset71
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset72 = Ltmp200-Lfunc_begin0
	.quad	Lset72
Lset73 = Ltmp204-Lfunc_begin0
	.quad	Lset73
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset74 = Ltmp205-Lfunc_begin0
	.quad	Lset74
Lset75 = Ltmp209-Lfunc_begin0
	.quad	Lset75
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset76 = Ltmp214-Lfunc_begin0
	.quad	Lset76
Lset77 = Ltmp215-Lfunc_begin0
	.quad	Lset77
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset78 = Ltmp219-Lfunc_begin0
	.quad	Lset78
Lset79 = Ltmp222-Lfunc_begin0
	.quad	Lset79
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset80 = Ltmp223-Lfunc_begin0
	.quad	Lset80
Lset81 = Ltmp226-Lfunc_begin0
	.quad	Lset81
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset82 = Ltmp228-Lfunc_begin0
	.quad	Lset82
Lset83 = Ltmp229-Lfunc_begin0
	.quad	Lset83
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset84 = Ltmp234-Lfunc_begin0
	.quad	Lset84
Lset85 = Ltmp235-Lfunc_begin0
	.quad	Lset85
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset86 = Ltmp237-Lfunc_begin0
	.quad	Lset86
Lset87 = Ltmp239-Lfunc_begin0
	.quad	Lset87
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset88 = Ltmp243-Lfunc_begin0
	.quad	Lset88
Lset89 = Ltmp245-Lfunc_begin0
	.quad	Lset89
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset90 = Ltmp246-Lfunc_begin0
	.quad	Lset90
Lset91 = Ltmp247-Lfunc_begin0
	.quad	Lset91
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset92 = Ltmp248-Lfunc_begin0
	.quad	Lset92
Lset93 = Ltmp249-Lfunc_begin0
	.quad	Lset93
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset94 = Ltmp250-Lfunc_begin0
	.quad	Lset94
Lset95 = Ltmp253-Lfunc_begin0
	.quad	Lset95
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset96 = Ltmp254-Lfunc_begin0
	.quad	Lset96
Lset97 = Ltmp255-Lfunc_begin0
	.quad	Lset97
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset98 = Ltmp256-Lfunc_begin0
	.quad	Lset98
Lset99 = Ltmp260-Lfunc_begin0
	.quad	Lset99
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset100 = Ltmp261-Lfunc_begin0
	.quad	Lset100
Lset101 = Ltmp262-Lfunc_begin0
	.quad	Lset101
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset102 = Ltmp264-Lfunc_begin0
	.quad	Lset102
Lset103 = Ltmp265-Lfunc_begin0
	.quad	Lset103
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset104 = Ltmp266-Lfunc_begin0
	.quad	Lset104
Lset105 = Ltmp267-Lfunc_begin0
	.quad	Lset105
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset106 = Ltmp270-Lfunc_begin0
	.quad	Lset106
Lset107 = Ltmp271-Lfunc_begin0
	.quad	Lset107
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset108 = Ltmp277-Lfunc_begin0
	.quad	Lset108
Lset109 = Ltmp283-Lfunc_begin0
	.quad	Lset109
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset110 = Ltmp285-Lfunc_begin0
	.quad	Lset110
Lset111 = Ltmp286-Lfunc_begin0
	.quad	Lset111
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset112 = Ltmp287-Lfunc_begin0
	.quad	Lset112
Lset113 = Ltmp289-Lfunc_begin0
	.quad	Lset113
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset114 = Ltmp292-Lfunc_begin0
	.quad	Lset114
Lset115 = Ltmp296-Lfunc_begin0
	.quad	Lset115
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset116 = Ltmp298-Lfunc_begin0
	.quad	Lset116
Lset117 = Ltmp299-Lfunc_begin0
	.quad	Lset117
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset118 = Ltmp300-Lfunc_begin0
	.quad	Lset118
Lset119 = Ltmp301-Lfunc_begin0
	.quad	Lset119
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset120 = Ltmp302-Lfunc_begin0
	.quad	Lset120
Lset121 = Ltmp303-Lfunc_begin0
	.quad	Lset121
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset122 = Ltmp305-Lfunc_begin0
	.quad	Lset122
Lset123 = Ltmp311-Lfunc_begin0
	.quad	Lset123
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset124 = Ltmp313-Lfunc_begin0
	.quad	Lset124
Lset125 = Ltmp314-Lfunc_begin0
	.quad	Lset125
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset126 = Ltmp315-Lfunc_begin0
	.quad	Lset126
Lset127 = Ltmp316-Lfunc_begin0
	.quad	Lset127
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset128 = Ltmp317-Lfunc_begin0
	.quad	Lset128
Lset129 = Ltmp319-Lfunc_begin0
	.quad	Lset129
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset130 = Ltmp320-Lfunc_begin0
	.quad	Lset130
Lset131 = Ltmp321-Lfunc_begin0
	.quad	Lset131
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset132 = Ltmp324-Lfunc_begin0
	.quad	Lset132
Lset133 = Ltmp326-Lfunc_begin0
	.quad	Lset133
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc1:
Lset134 = Lfunc_begin0-Lfunc_begin0
	.quad	Lset134
Lset135 = Ltmp8-Lfunc_begin0
	.quad	Lset135
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
Lset136 = Ltmp8-Lfunc_begin0
	.quad	Lset136
Lset137 = Lfunc_end0-Lfunc_begin0
	.quad	Lset137
	.short	3                       ## Loc expr size
	.byte	118                     ## DW_OP_breg6
	.byte	160                     ## -2528
	.byte	108                     ## 
	.quad	0
	.quad	0
Ldebug_loc2:
Lset138 = Ltmp9-Lfunc_begin0
	.quad	Lset138
Lset139 = Ltmp89-Lfunc_begin0
	.quad	Lset139
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset140 = Ltmp89-Lfunc_begin0
	.quad	Lset140
Lset141 = Ltmp105-Lfunc_begin0
	.quad	Lset141
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset142 = Ltmp105-Lfunc_begin0
	.quad	Lset142
Lset143 = Ltmp248-Lfunc_begin0
	.quad	Lset143
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset144 = Ltmp248-Lfunc_begin0
	.quad	Lset144
Lset145 = Ltmp250-Lfunc_begin0
	.quad	Lset145
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset146 = Ltmp250-Lfunc_begin0
	.quad	Lset146
Lset147 = Ltmp257-Lfunc_begin0
	.quad	Lset147
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset148 = Ltmp257-Lfunc_begin0
	.quad	Lset148
Lset149 = Ltmp264-Lfunc_begin0
	.quad	Lset149
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset150 = Ltmp264-Lfunc_begin0
	.quad	Lset150
Lset151 = Ltmp270-Lfunc_begin0
	.quad	Lset151
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset152 = Ltmp270-Lfunc_begin0
	.quad	Lset152
Lset153 = Lfunc_end0-Lfunc_begin0
	.quad	Lset153
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
	.quad	0
	.quad	0
Ldebug_loc3:
Lset154 = Ltmp9-Lfunc_begin0
	.quad	Lset154
Lset155 = Ltmp112-Lfunc_begin0
	.quad	Lset155
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset156 = Ltmp112-Lfunc_begin0
	.quad	Lset156
Lset157 = Ltmp248-Lfunc_begin0
	.quad	Lset157
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset158 = Ltmp248-Lfunc_begin0
	.quad	Lset158
Lset159 = Ltmp252-Lfunc_begin0
	.quad	Lset159
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset160 = Ltmp252-Lfunc_begin0
	.quad	Lset160
Lset161 = Ltmp256-Lfunc_begin0
	.quad	Lset161
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset162 = Ltmp256-Lfunc_begin0
	.quad	Lset162
Lset163 = Ltmp264-Lfunc_begin0
	.quad	Lset163
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset164 = Ltmp264-Lfunc_begin0
	.quad	Lset164
Lset165 = Ltmp270-Lfunc_begin0
	.quad	Lset165
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset166 = Ltmp270-Lfunc_begin0
	.quad	Lset166
Lset167 = Lfunc_end0-Lfunc_begin0
	.quad	Lset167
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc4:
Lset168 = Ltmp9-Lfunc_begin0
	.quad	Lset168
Lset169 = Ltmp140-Lfunc_begin0
	.quad	Lset169
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset170 = Ltmp140-Lfunc_begin0
	.quad	Lset170
Lset171 = Ltmp246-Lfunc_begin0
	.quad	Lset171
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset172 = Ltmp246-Lfunc_begin0
	.quad	Lset172
Lset173 = Ltmp252-Lfunc_begin0
	.quad	Lset173
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset174 = Ltmp252-Lfunc_begin0
	.quad	Lset174
Lset175 = Ltmp256-Lfunc_begin0
	.quad	Lset175
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset176 = Ltmp256-Lfunc_begin0
	.quad	Lset176
Lset177 = Ltmp264-Lfunc_begin0
	.quad	Lset177
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset178 = Ltmp264-Lfunc_begin0
	.quad	Lset178
Lset179 = Ltmp270-Lfunc_begin0
	.quad	Lset179
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset180 = Ltmp270-Lfunc_begin0
	.quad	Lset180
Lset181 = Lfunc_end0-Lfunc_begin0
	.quad	Lset181
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc5:
Lset182 = Ltmp10-Lfunc_begin0
	.quad	Lset182
Lset183 = Ltmp229-Lfunc_begin0
	.quad	Lset183
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset184 = Ltmp234-Lfunc_begin0
	.quad	Lset184
Lset185 = Ltmp234-Lfunc_begin0
	.quad	Lset185
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset186 = Ltmp237-Lfunc_begin0
	.quad	Lset186
Lset187 = Ltmp237-Lfunc_begin0
	.quad	Lset187
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset188 = Ltmp243-Lfunc_begin0
	.quad	Lset188
Lset189 = Ltmp243-Lfunc_begin0
	.quad	Lset189
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset190 = Ltmp244-Lfunc_begin0
	.quad	Lset190
Lset191 = Ltmp244-Lfunc_begin0
	.quad	Lset191
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset192 = Ltmp246-Lfunc_begin0
	.quad	Lset192
Lset193 = Lfunc_end0-Lfunc_begin0
	.quad	Lset193
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc6:
Lset194 = Ltmp11-Lfunc_begin0
	.quad	Lset194
Lset195 = Ltmp34-Lfunc_begin0
	.quad	Lset195
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset196 = Ltmp34-Lfunc_begin0
	.quad	Lset196
Lset197 = Ltmp36-Lfunc_begin0
	.quad	Lset197
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset198 = Ltmp36-Lfunc_begin0
	.quad	Lset198
Lset199 = Lfunc_end0-Lfunc_begin0
	.quad	Lset199
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc7:
Lset200 = Ltmp12-Lfunc_begin0
	.quad	Lset200
Lset201 = Ltmp129-Lfunc_begin0
	.quad	Lset201
	.short	2                       ## Loc expr size
	.byte	16                      ## DW_OP_constu
	.byte	0                       ## 0
Lset202 = Ltmp129-Lfunc_begin0
	.quad	Lset202
Lset203 = Ltmp130-Lfunc_begin0
	.quad	Lset203
	.short	3                       ## Loc expr size
	.byte	118                     ## DW_OP_breg6
	.byte	172                     ## -2516
	.byte	108                     ## 
Lset204 = Ltmp130-Lfunc_begin0
	.quad	Lset204
Lset205 = Lfunc_end0-Lfunc_begin0
	.quad	Lset205
	.short	2                       ## Loc expr size
	.byte	16                      ## DW_OP_constu
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc8:
Lset206 = Ltmp13-Lfunc_begin0
	.quad	Lset206
Lset207 = Ltmp17-Lfunc_begin0
	.quad	Lset207
	.short	2                       ## Loc expr size
	.byte	116                     ## DW_OP_breg4
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc9:
Lset208 = Ltmp14-Lfunc_begin0
	.quad	Lset208
Lset209 = Ltmp17-Lfunc_begin0
	.quad	Lset209
	.short	2                       ## Loc expr size
	.byte	113                     ## DW_OP_breg1
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc10:
Lset210 = Ltmp16-Lfunc_begin0
	.quad	Lset210
Lset211 = Ltmp26-Lfunc_begin0
	.quad	Lset211
	.short	1                       ## Loc expr size
	.byte	83                      ## DW_OP_reg3
	.quad	0
	.quad	0
Ldebug_loc11:
Lset212 = Ltmp23-Lfunc_begin0
	.quad	Lset212
Lset213 = Ltmp24-Lfunc_begin0
	.quad	Lset213
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
Lset214 = Ltmp24-Lfunc_begin0
	.quad	Lset214
Lset215 = Lfunc_end0-Lfunc_begin0
	.quad	Lset215
	.short	3                       ## Loc expr size
	.byte	118                     ## DW_OP_breg6
	.byte	200                     ## -2488
	.byte	108                     ## 
	.quad	0
	.quad	0
Ldebug_loc12:
Lset216 = Ltmp25-Lfunc_begin0
	.quad	Lset216
Lset217 = Ltmp34-Lfunc_begin0
	.quad	Lset217
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset218 = Ltmp34-Lfunc_begin0
	.quad	Lset218
Lset219 = Ltmp36-Lfunc_begin0
	.quad	Lset219
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset220 = Ltmp36-Lfunc_begin0
	.quad	Lset220
Lset221 = Lfunc_end0-Lfunc_begin0
	.quad	Lset221
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
	.quad	0
	.quad	0
Ldebug_loc13:
Lset222 = Ltmp25-Lfunc_begin0
	.quad	Lset222
Lset223 = Ltmp27-Lfunc_begin0
	.quad	Lset223
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset224 = Ltmp40-Lfunc_begin0
	.quad	Lset224
Lset225 = Ltmp41-Lfunc_begin0
	.quad	Lset225
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
	.quad	0
	.quad	0
Ldebug_loc14:
Lset226 = Ltmp29-Lfunc_begin0
	.quad	Lset226
Lset227 = Ltmp36-Lfunc_begin0
	.quad	Lset227
	.short	1                       ## Loc expr size
	.byte	95                      ## DW_OP_reg15
	.quad	0
	.quad	0
Ldebug_loc15:
Lset228 = Ltmp29-Lfunc_begin0
	.quad	Lset228
Lset229 = Ltmp36-Lfunc_begin0
	.quad	Lset229
	.short	1                       ## Loc expr size
	.byte	95                      ## DW_OP_reg15
	.quad	0
	.quad	0
Ldebug_loc16:
Lset230 = Ltmp33-Lfunc_begin0
	.quad	Lset230
Lset231 = Ltmp36-Lfunc_begin0
	.quad	Lset231
	.short	2                       ## Loc expr size
	.byte	125                     ## DW_OP_breg13
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc17:
Lset232 = Ltmp48-Lfunc_begin0
	.quad	Lset232
Lset233 = Ltmp49-Lfunc_begin0
	.quad	Lset233
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset234 = Ltmp49-Lfunc_begin0
	.quad	Lset234
Lset235 = Ltmp54-Lfunc_begin0
	.quad	Lset235
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
Lset236 = Ltmp54-Lfunc_begin0
	.quad	Lset236
Lset237 = Ltmp54-Lfunc_begin0
	.quad	Lset237
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset238 = Ltmp54-Lfunc_begin0
	.quad	Lset238
Lset239 = Ltmp55-Lfunc_begin0
	.quad	Lset239
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
Lset240 = Ltmp55-Lfunc_begin0
	.quad	Lset240
Lset241 = Ltmp55-Lfunc_begin0
	.quad	Lset241
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset242 = Ltmp55-Lfunc_begin0
	.quad	Lset242
Lset243 = Ltmp56-Lfunc_begin0
	.quad	Lset243
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc18:
Lset244 = Ltmp53-Lfunc_begin0
	.quad	Lset244
Lset245 = Ltmp54-Lfunc_begin0
	.quad	Lset245
	.short	3                       ## Loc expr size
	.byte	82                      ## super-register DW_OP_reg2
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc19:
Lset246 = Ltmp59-Lfunc_begin0
	.quad	Lset246
Lset247 = Ltmp60-Lfunc_begin0
	.quad	Lset247
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset248 = Ltmp60-Lfunc_begin0
	.quad	Lset248
Lset249 = Ltmp66-Lfunc_begin0
	.quad	Lset249
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
Lset250 = Ltmp66-Lfunc_begin0
	.quad	Lset250
Lset251 = Ltmp66-Lfunc_begin0
	.quad	Lset251
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset252 = Ltmp66-Lfunc_begin0
	.quad	Lset252
Lset253 = Ltmp67-Lfunc_begin0
	.quad	Lset253
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
Lset254 = Ltmp67-Lfunc_begin0
	.quad	Lset254
Lset255 = Ltmp67-Lfunc_begin0
	.quad	Lset255
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset256 = Ltmp67-Lfunc_begin0
	.quad	Lset256
Lset257 = Ltmp68-Lfunc_begin0
	.quad	Lset257
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc20:
Lset258 = Ltmp65-Lfunc_begin0
	.quad	Lset258
Lset259 = Ltmp66-Lfunc_begin0
	.quad	Lset259
	.short	3                       ## Loc expr size
	.byte	82                      ## super-register DW_OP_reg2
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc21:
Lset260 = Ltmp75-Lfunc_begin0
	.quad	Lset260
Lset261 = Ltmp77-Lfunc_begin0
	.quad	Lset261
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc22:
Lset262 = Ltmp82-Lfunc_begin0
	.quad	Lset262
Lset263 = Ltmp84-Lfunc_begin0
	.quad	Lset263
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc23:
Lset264 = Ltmp94-Lfunc_begin0
	.quad	Lset264
Lset265 = Ltmp95-Lfunc_begin0
	.quad	Lset265
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc24:
Lset266 = Ltmp101-Lfunc_begin0
	.quad	Lset266
Lset267 = Ltmp103-Lfunc_begin0
	.quad	Lset267
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc25:
Lset268 = Ltmp102-Lfunc_begin0
	.quad	Lset268
Lset269 = Ltmp105-Lfunc_begin0
	.quad	Lset269
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
	.quad	0
	.quad	0
Ldebug_loc26:
Lset270 = Ltmp134-Lfunc_begin0
	.quad	Lset270
Lset271 = Ltmp135-Lfunc_begin0
	.quad	Lset271
	.short	4                       ## Loc expr size
	.byte	16                      ## DW_OP_constu
	.byte	128                     ## 524288
	.byte	128                     ## 
	.byte	32                      ## 
	.quad	0
	.quad	0
Ldebug_loc27:
Lset272 = Ltmp142-Lfunc_begin0
	.quad	Lset272
Lset273 = Ltmp143-Lfunc_begin0
	.quad	Lset273
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
Lset274 = Ltmp147-Lfunc_begin0
	.quad	Lset274
Lset275 = Ltmp148-Lfunc_begin0
	.quad	Lset275
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc28:
Lset276 = Ltmp159-Lfunc_begin0
	.quad	Lset276
Lset277 = Ltmp167-Lfunc_begin0
	.quad	Lset277
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset278 = Ltmp167-Lfunc_begin0
	.quad	Lset278
Lset279 = Ltmp168-Lfunc_begin0
	.quad	Lset279
	.short	3                       ## Loc expr size
	.byte	95                      ## super-register DW_OP_reg15
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset280 = Ltmp169-Lfunc_begin0
	.quad	Lset280
Lset281 = Lfunc_end0-Lfunc_begin0
	.quad	Lset281
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc29:
Lset282 = Ltmp159-Lfunc_begin0
	.quad	Lset282
Lset283 = Ltmp174-Lfunc_begin0
	.quad	Lset283
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset284 = Ltmp174-Lfunc_begin0
	.quad	Lset284
Lset285 = Ltmp175-Lfunc_begin0
	.quad	Lset285
	.short	3                       ## Loc expr size
	.byte	118                     ## DW_OP_breg6
	.byte	200                     ## -2488
	.byte	108                     ## 
Lset286 = Ltmp175-Lfunc_begin0
	.quad	Lset286
Lset287 = Ltmp176-Lfunc_begin0
	.quad	Lset287
	.short	3                       ## Loc expr size
	.byte	81                      ## super-register DW_OP_reg1
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset288 = Ltmp177-Lfunc_begin0
	.quad	Lset288
Lset289 = Lfunc_end0-Lfunc_begin0
	.quad	Lset289
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
	.quad	0
	.quad	0
Ldebug_loc30:
Lset290 = Ltmp163-Lfunc_begin0
	.quad	Lset290
Lset291 = Ltmp169-Lfunc_begin0
	.quad	Lset291
	.short	1                       ## Loc expr size
	.byte	83                      ## DW_OP_reg3
	.quad	0
	.quad	0
Ldebug_loc31:
Lset292 = Ltmp187-Lfunc_begin0
	.quad	Lset292
Lset293 = Ltmp190-Lfunc_begin0
	.quad	Lset293
	.short	1                       ## Loc expr size
	.byte	83                      ## DW_OP_reg3
	.quad	0
	.quad	0
Ldebug_loc32:
Lset294 = Ltmp201-Lfunc_begin0
	.quad	Lset294
Lset295 = Ltmp202-Lfunc_begin0
	.quad	Lset295
	.short	3                       ## Loc expr size
	.byte	80                      ## super-register DW_OP_reg0
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc33:
Lset296 = Ltmp211-Lfunc_begin0
	.quad	Lset296
Lset297 = Ltmp214-Lfunc_begin0
	.quad	Lset297
	.short	3                       ## Loc expr size
	.byte	83                      ## super-register DW_OP_reg3
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc34:
Lset298 = Ltmp211-Lfunc_begin0
	.quad	Lset298
Lset299 = Ltmp214-Lfunc_begin0
	.quad	Lset299
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
Lset300 = Ltmp216-Lfunc_begin0
	.quad	Lset300
Lset301 = Ltmp219-Lfunc_begin0
	.quad	Lset301
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc35:
Lset302 = Ltmp212-Lfunc_begin0
	.quad	Lset302
Lset303 = Ltmp214-Lfunc_begin0
	.quad	Lset303
	.short	3                       ## Loc expr size
	.byte	82                      ## super-register DW_OP_reg2
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset304 = Ltmp218-Lfunc_begin0
	.quad	Lset304
Lset305 = Ltmp219-Lfunc_begin0
	.quad	Lset305
	.short	3                       ## Loc expr size
	.byte	82                      ## super-register DW_OP_reg2
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc36:
Lset306 = Ltmp231-Lfunc_begin0
	.quad	Lset306
Lset307 = Ltmp232-Lfunc_begin0
	.quad	Lset307
	.short	1                       ## Loc expr size
	.byte	82                      ## DW_OP_reg2
	.quad	0
	.quad	0
Ldebug_loc37:
Lset308 = Ltmp236-Lfunc_begin0
	.quad	Lset308
Lset309 = Ltmp237-Lfunc_begin0
	.quad	Lset309
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset310 = Ltmp237-Lfunc_begin0
	.quad	Lset310
Lset311 = Ltmp243-Lfunc_begin0
	.quad	Lset311
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
Lset312 = Ltmp243-Lfunc_begin0
	.quad	Lset312
Lset313 = Ltmp243-Lfunc_begin0
	.quad	Lset313
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset314 = Ltmp243-Lfunc_begin0
	.quad	Lset314
Lset315 = Ltmp244-Lfunc_begin0
	.quad	Lset315
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
Lset316 = Ltmp244-Lfunc_begin0
	.quad	Lset316
Lset317 = Ltmp244-Lfunc_begin0
	.quad	Lset317
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset318 = Ltmp244-Lfunc_begin0
	.quad	Lset318
Lset319 = Ltmp245-Lfunc_begin0
	.quad	Lset319
	.short	2                       ## Loc expr size
	.byte	124                     ## DW_OP_breg12
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc38:
Lset320 = Ltmp242-Lfunc_begin0
	.quad	Lset320
Lset321 = Ltmp243-Lfunc_begin0
	.quad	Lset321
	.short	3                       ## Loc expr size
	.byte	82                      ## super-register DW_OP_reg2
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc39:
Lset322 = Ltmp261-Lfunc_begin0
	.quad	Lset322
Lset323 = Ltmp262-Lfunc_begin0
	.quad	Lset323
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc40:
Lset324 = Ltmp272-Lfunc_begin0
	.quad	Lset324
Lset325 = Ltmp273-Lfunc_begin0
	.quad	Lset325
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc41:
Lset326 = Ltmp274-Lfunc_begin0
	.quad	Lset326
Lset327 = Ltmp290-Lfunc_begin0
	.quad	Lset327
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset328 = Ltmp290-Lfunc_begin0
	.quad	Lset328
Lset329 = Ltmp298-Lfunc_begin0
	.quad	Lset329
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset330 = Ltmp298-Lfunc_begin0
	.quad	Lset330
Lset331 = Ltmp305-Lfunc_begin0
	.quad	Lset331
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset332 = Ltmp305-Lfunc_begin0
	.quad	Lset332
Lset333 = Ltmp318-Lfunc_begin0
	.quad	Lset333
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset334 = Ltmp318-Lfunc_begin0
	.quad	Lset334
Lset335 = Ltmp320-Lfunc_begin0
	.quad	Lset335
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset336 = Ltmp320-Lfunc_begin0
	.quad	Lset336
Lset337 = Lfunc_end0-Lfunc_begin0
	.quad	Lset337
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
	.quad	0
	.quad	0
Ldebug_loc42:
Lset338 = Ltmp274-Lfunc_begin0
	.quad	Lset338
Lset339 = Ltmp290-Lfunc_begin0
	.quad	Lset339
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset340 = Ltmp290-Lfunc_begin0
	.quad	Lset340
Lset341 = Ltmp294-Lfunc_begin0
	.quad	Lset341
	.short	3                       ## Loc expr size
	.byte	95                      ## super-register DW_OP_reg15
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset342 = Ltmp298-Lfunc_begin0
	.quad	Lset342
Lset343 = Lfunc_end0-Lfunc_begin0
	.quad	Lset343
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc43:
Lset344 = Ltmp279-Lfunc_begin0
	.quad	Lset344
Lset345 = Ltmp280-Lfunc_begin0
	.quad	Lset345
	.short	3                       ## Loc expr size
	.byte	80                      ## super-register DW_OP_reg0
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc44:
Lset346 = Lfunc_begin2-Lfunc_begin0
	.quad	Lset346
Lset347 = Ltmp339-Lfunc_begin0
	.quad	Lset347
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
Lset348 = Ltmp339-Lfunc_begin0
	.quad	Lset348
Lset349 = Ltmp345-Lfunc_begin0
	.quad	Lset349
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset350 = Ltmp345-Lfunc_begin0
	.quad	Lset350
Lset351 = Ltmp347-Lfunc_begin0
	.quad	Lset351
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
	.quad	0
	.quad	0
Ldebug_loc45:
Lset352 = Ltmp343-Lfunc_begin0
	.quad	Lset352
Lset353 = Ltmp348-Lfunc_begin0
	.quad	Lset353
	.short	3                       ## Loc expr size
	.byte	83                      ## super-register DW_OP_reg3
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc46:
Lset354 = Lfunc_begin3-Lfunc_begin0
	.quad	Lset354
Lset355 = Ltmp357-Lfunc_begin0
	.quad	Lset355
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
	.quad	0
	.quad	0
Ldebug_loc47:
Lset356 = Lfunc_begin4-Lfunc_begin0
	.quad	Lset356
Lset357 = Ltmp368-Lfunc_begin0
	.quad	Lset357
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
Lset358 = Ltmp368-Lfunc_begin0
	.quad	Lset358
Lset359 = Ltmp370-Lfunc_begin0
	.quad	Lset359
	.short	1                       ## Loc expr size
	.byte	95                      ## DW_OP_reg15
Lset360 = Ltmp370-Lfunc_begin0
	.quad	Lset360
Lset361 = Ltmp373-Lfunc_begin0
	.quad	Lset361
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
	.quad	0
	.quad	0
Ldebug_loc48:
Lset362 = Lfunc_begin4-Lfunc_begin0
	.quad	Lset362
Lset363 = Ltmp367-Lfunc_begin0
	.quad	Lset363
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
Lset364 = Ltmp367-Lfunc_begin0
	.quad	Lset364
Lset365 = Ltmp371-Lfunc_begin0
	.quad	Lset365
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset366 = Ltmp371-Lfunc_begin0
	.quad	Lset366
Lset367 = Ltmp373-Lfunc_begin0
	.quad	Lset367
	.short	1                       ## Loc expr size
	.byte	81                      ## DW_OP_reg1
	.quad	0
	.quad	0
Ldebug_loc49:
Lset368 = Ltmp369-Lfunc_begin0
	.quad	Lset368
Lset369 = Ltmp374-Lfunc_begin0
	.quad	Lset369
	.short	3                       ## Loc expr size
	.byte	92                      ## super-register DW_OP_reg12
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc50:
Lset370 = Lfunc_begin6-Lfunc_begin0
	.quad	Lset370
Lset371 = Ltmp391-Lfunc_begin0
	.quad	Lset371
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset372 = Ltmp391-Lfunc_begin0
	.quad	Lset372
Lset373 = Ltmp392-Lfunc_begin0
	.quad	Lset373
	.short	3                       ## Loc expr size
	.byte	83                      ## super-register DW_OP_reg3
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset374 = Ltmp393-Lfunc_begin0
	.quad	Lset374
Lset375 = Ltmp399-Lfunc_begin0
	.quad	Lset375
	.short	3                       ## Loc expr size
	.byte	83                      ## super-register DW_OP_reg3
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset376 = Ltmp401-Lfunc_begin0
	.quad	Lset376
Lset377 = Ltmp407-Lfunc_begin0
	.quad	Lset377
	.short	3                       ## Loc expr size
	.byte	83                      ## super-register DW_OP_reg3
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc51:
Lset378 = Lfunc_begin6-Lfunc_begin0
	.quad	Lset378
Lset379 = Ltmp390-Lfunc_begin0
	.quad	Lset379
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
Lset380 = Ltmp390-Lfunc_begin0
	.quad	Lset380
Lset381 = Ltmp392-Lfunc_begin0
	.quad	Lset381
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset382 = Ltmp393-Lfunc_begin0
	.quad	Lset382
Lset383 = Ltmp399-Lfunc_begin0
	.quad	Lset383
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset384 = Ltmp401-Lfunc_begin0
	.quad	Lset384
Lset385 = Lfunc_end6-Lfunc_begin0
	.quad	Lset385
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
	.quad	0
	.quad	0
Ldebug_loc52:
Lset386 = Ltmp395-Lfunc_begin0
	.quad	Lset386
Lset387 = Ltmp397-Lfunc_begin0
	.quad	Lset387
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
	.quad	0
	.quad	0
Ldebug_loc53:
Lset388 = Ltmp398-Lfunc_begin0
	.quad	Lset388
Lset389 = Ltmp399-Lfunc_begin0
	.quad	Lset389
	.short	3                       ## Loc expr size
	.byte	80                      ## super-register DW_OP_reg0
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc54:
Lset390 = Ltmp403-Lfunc_begin0
	.quad	Lset390
Lset391 = Ltmp405-Lfunc_begin0
	.quad	Lset391
	.short	3                       ## Loc expr size
	.byte	95                      ## super-register DW_OP_reg15
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc55:
Lset392 = Ltmp404-Lfunc_begin0
	.quad	Lset392
Lset393 = Ltmp405-Lfunc_begin0
	.quad	Lset393
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
	.quad	0
	.quad	0
	.section	__DWARF,__debug_abbrev,regular,debug
Lsection_abbrev:
	.byte	1                       ## Abbreviation Code
	.byte	17                      ## DW_TAG_compile_unit
	.byte	1                       ## DW_CHILDREN_yes
	.byte	37                      ## DW_AT_producer
	.byte	14                      ## DW_FORM_strp
	.byte	19                      ## DW_AT_language
	.byte	5                       ## DW_FORM_data2
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	16                      ## DW_AT_stmt_list
	.byte	6                       ## DW_FORM_data4
	.byte	27                      ## DW_AT_comp_dir
	.byte	14                      ## DW_FORM_strp
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	12                      ## DW_FORM_flag
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	2                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	63                      ## DW_AT_external
	.byte	12                      ## DW_FORM_flag
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	3                       ## Abbreviation Code
	.byte	36                      ## DW_TAG_base_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	62                      ## DW_AT_encoding
	.byte	11                      ## DW_FORM_data1
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	4                       ## Abbreviation Code
	.byte	22                      ## DW_TAG_typedef
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	5                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	6                       ## Abbreviation Code
	.byte	15                      ## DW_TAG_pointer_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	7                       ## Abbreviation Code
	.byte	38                      ## DW_TAG_const_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	8                       ## Abbreviation Code
	.byte	15                      ## DW_TAG_pointer_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	9                       ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	39                      ## DW_AT_prototyped
	.byte	12                      ## DW_FORM_flag
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	12                      ## DW_FORM_flag
	.byte	32                      ## DW_AT_inline
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	10                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	11                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	12                      ## Abbreviation Code
	.byte	19                      ## DW_TAG_structure_type
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	13                      ## Abbreviation Code
	.byte	13                      ## DW_TAG_member
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	56                      ## DW_AT_data_member_location
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	14                      ## Abbreviation Code
	.byte	1                       ## DW_TAG_array_type
	.byte	1                       ## DW_CHILDREN_yes
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	15                      ## Abbreviation Code
	.byte	33                      ## DW_TAG_subrange_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	55                      ## DW_AT_count
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	16                      ## Abbreviation Code
	.byte	36                      ## DW_TAG_base_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	62                      ## DW_AT_encoding
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	17                      ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	39                      ## DW_AT_prototyped
	.byte	12                      ## DW_FORM_flag
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	12                      ## DW_FORM_flag
	.byte	32                      ## DW_AT_inline
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	18                      ## Abbreviation Code
	.byte	11                      ## DW_TAG_lexical_block
	.byte	1                       ## DW_CHILDREN_yes
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	19                      ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	39                      ## DW_AT_prototyped
	.byte	12                      ## DW_FORM_flag
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	12                      ## DW_FORM_flag
	.byte	32                      ## DW_AT_inline
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	20                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	21                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	22                      ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	39                      ## DW_AT_prototyped
	.byte	12                      ## DW_FORM_flag
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	12                      ## DW_FORM_flag
	.byte	32                      ## DW_AT_inline
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	23                      ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	64                      ## DW_AT_frame_base
	.byte	10                      ## DW_FORM_block1
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	39                      ## DW_AT_prototyped
	.byte	12                      ## DW_FORM_flag
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	63                      ## DW_AT_external
	.byte	12                      ## DW_FORM_flag
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	12                      ## DW_FORM_flag
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	24                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	6                       ## DW_FORM_data4
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	25                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	26                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	6                       ## DW_FORM_data4
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	27                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	28                      ## DW_AT_const_value
	.byte	13                      ## DW_FORM_sdata
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	28                      ## Abbreviation Code
	.byte	29                      ## DW_TAG_inlined_subroutine
	.byte	1                       ## DW_CHILDREN_yes
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	85                      ## DW_AT_ranges
	.byte	6                       ## DW_FORM_data4
	.byte	88                      ## DW_AT_call_file
	.byte	11                      ## DW_FORM_data1
	.byte	89                      ## DW_AT_call_line
	.byte	5                       ## DW_FORM_data2
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	29                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	6                       ## DW_FORM_data4
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	30                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	6                       ## DW_FORM_data4
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	31                      ## Abbreviation Code
	.byte	11                      ## DW_TAG_lexical_block
	.byte	1                       ## DW_CHILDREN_yes
	.byte	85                      ## DW_AT_ranges
	.byte	6                       ## DW_FORM_data4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	32                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	28                      ## DW_AT_const_value
	.byte	13                      ## DW_FORM_sdata
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	33                      ## Abbreviation Code
	.byte	29                      ## DW_TAG_inlined_subroutine
	.byte	1                       ## DW_CHILDREN_yes
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	85                      ## DW_AT_ranges
	.byte	6                       ## DW_FORM_data4
	.byte	88                      ## DW_AT_call_file
	.byte	11                      ## DW_FORM_data1
	.byte	89                      ## DW_AT_call_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	34                      ## Abbreviation Code
	.byte	29                      ## DW_TAG_inlined_subroutine
	.byte	0                       ## DW_CHILDREN_no
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	88                      ## DW_AT_call_file
	.byte	11                      ## DW_FORM_data1
	.byte	89                      ## DW_AT_call_line
	.byte	5                       ## DW_FORM_data2
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	35                      ## Abbreviation Code
	.byte	29                      ## DW_TAG_inlined_subroutine
	.byte	1                       ## DW_CHILDREN_yes
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	88                      ## DW_AT_call_file
	.byte	11                      ## DW_FORM_data1
	.byte	89                      ## DW_AT_call_line
	.byte	5                       ## DW_FORM_data2
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	36                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	37                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	28                      ## DW_AT_const_value
	.byte	13                      ## DW_FORM_sdata
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	38                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	39                      ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	64                      ## DW_AT_frame_base
	.byte	10                      ## DW_FORM_block1
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	39                      ## DW_AT_prototyped
	.byte	12                      ## DW_FORM_flag
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	12                      ## DW_FORM_flag
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	40                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	41                      ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	64                      ## DW_AT_frame_base
	.byte	10                      ## DW_FORM_block1
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	39                      ## DW_AT_prototyped
	.byte	12                      ## DW_FORM_flag
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	12                      ## DW_FORM_flag
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	42                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	6                       ## DW_FORM_data4
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	43                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	10                      ## DW_FORM_block1
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	44                      ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	6                       ## DW_FORM_data4
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	45                      ## Abbreviation Code
	.byte	24                      ## DW_TAG_unspecified_parameters
	.byte	0                       ## DW_CHILDREN_no
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	46                      ## Abbreviation Code
	.byte	11                      ## DW_TAG_lexical_block
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	47                      ## Abbreviation Code
	.byte	29                      ## DW_TAG_inlined_subroutine
	.byte	1                       ## DW_CHILDREN_yes
	.byte	49                      ## DW_AT_abstract_origin
	.byte	19                      ## DW_FORM_ref4
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	1                       ## DW_FORM_addr
	.byte	88                      ## DW_AT_call_file
	.byte	11                      ## DW_FORM_data1
	.byte	89                      ## DW_AT_call_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	48                      ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	39                      ## DW_AT_prototyped
	.byte	12                      ## DW_FORM_flag
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	63                      ## DW_AT_external
	.byte	12                      ## DW_FORM_flag
	.ascii	"\341\177"              ## DW_AT_APPLE_optimized
	.byte	12                      ## DW_FORM_flag
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	49                      ## Abbreviation Code
	.byte	33                      ## DW_TAG_subrange_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	55                      ## DW_AT_count
	.byte	5                       ## DW_FORM_data2
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	50                      ## Abbreviation Code
	.byte	19                      ## DW_TAG_structure_type
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	51                      ## Abbreviation Code
	.byte	13                      ## DW_TAG_member
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	56                      ## DW_AT_data_member_location
	.byte	10                      ## DW_FORM_block1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	52                      ## Abbreviation Code
	.byte	23                      ## DW_TAG_union_type
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	5                       ## DW_FORM_data2
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	53                      ## Abbreviation Code
	.byte	21                      ## DW_TAG_subroutine_type
	.byte	1                       ## DW_CHILDREN_yes
	.byte	39                      ## DW_AT_prototyped
	.byte	12                      ## DW_FORM_flag
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	54                      ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	55                      ## Abbreviation Code
	.byte	23                      ## DW_TAG_union_type
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	0                       ## EOM(3)
	.section	__DWARF,__debug_info,regular,debug
Lsection_info:
Lcu_begin0:
	.long	4148                    ## Length of Unit
	.short	2                       ## DWARF version number
Lset394 = Lsection_abbrev-Lsection_abbrev ## Offset Into Abbrev. Section
	.long	Lset394
	.byte	8                       ## Address Size (in bytes)
	.byte	1                       ## Abbrev [1] 0xb:0x102d DW_TAG_compile_unit
	.long	0                       ## DW_AT_producer
	.short	12                      ## DW_AT_language
	.long	42                      ## DW_AT_name
Lset395 = Lline_table_start0-Lsection_line ## DW_AT_stmt_list
	.long	Lset395
	.long	52                      ## DW_AT_comp_dir
	.byte	1                       ## DW_AT_APPLE_optimized
	.quad	Lfunc_begin0            ## DW_AT_low_pc
	.quad	Lfunc_end6              ## DW_AT_high_pc
	.byte	2                       ## Abbrev [2] 0x2f:0x16 DW_TAG_variable
	.long	72                      ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_decl_file
	.byte	27                      ## DW_AT_decl_line
	.byte	9                       ## DW_AT_location
	.byte	3
	.quad	_isSignal
	.byte	3                       ## Abbrev [3] 0x45:0x7 DW_TAG_base_type
	.long	81                      ## DW_AT_name
	.byte	5                       ## DW_AT_encoding
	.byte	4                       ## DW_AT_byte_size
	.byte	2                       ## Abbrev [2] 0x4c:0x16 DW_TAG_variable
	.long	85                      ## DW_AT_name
	.long	98                      ## DW_AT_type
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_decl_file
	.byte	211                     ## DW_AT_decl_line
	.byte	9                       ## DW_AT_location
	.byte	3
	.quad	_foreground
	.byte	4                       ## Abbrev [4] 0x62:0xb DW_TAG_typedef
	.long	109                     ## DW_AT_type
	.long	96                      ## DW_AT_name
	.byte	4                       ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x6d:0xb DW_TAG_typedef
	.long	120                     ## DW_AT_type
	.long	102                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	72                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x78:0xb DW_TAG_typedef
	.long	69                      ## DW_AT_type
	.long	117                     ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	44                      ## DW_AT_decl_line
	.byte	5                       ## Abbrev [5] 0x83:0x15 DW_TAG_variable
	.long	127                     ## DW_AT_name
	.long	152                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	177                     ## DW_AT_decl_line
	.byte	9                       ## DW_AT_location
	.byte	3
	.quad	_arg0
	.byte	6                       ## Abbrev [6] 0x98:0x5 DW_TAG_pointer_type
	.long	157                     ## DW_AT_type
	.byte	7                       ## Abbrev [7] 0x9d:0x5 DW_TAG_const_type
	.long	162                     ## DW_AT_type
	.byte	3                       ## Abbrev [3] 0xa2:0x7 DW_TAG_base_type
	.long	132                     ## DW_AT_name
	.byte	6                       ## DW_AT_encoding
	.byte	1                       ## DW_AT_byte_size
	.byte	8                       ## Abbrev [8] 0xa9:0x1 DW_TAG_pointer_type
	.byte	6                       ## Abbrev [6] 0xaa:0x5 DW_TAG_pointer_type
	.long	162                     ## DW_AT_type
	.byte	9                       ## Abbrev [9] 0xaf:0x28 DW_TAG_subprogram
	.long	137                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	350                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.long	69                      ## DW_AT_type
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	10                      ## Abbrev [10] 0xbe:0xc DW_TAG_formal_parameter
	.long	148                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	350                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0xca:0xc DW_TAG_variable
	.long	157                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	352                     ## DW_AT_decl_line
	.long	215                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	12                      ## Abbrev [12] 0xd7:0x13e DW_TAG_structure_type
	.long	164                     ## DW_AT_name
	.byte	144                     ## DW_AT_byte_size
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xdf:0xe DW_TAG_member
	.long	169                     ## DW_AT_name
	.long	533                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xed:0xe DW_TAG_member
	.long	197                     ## DW_AT_name
	.long	555                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	13                      ## Abbrev [13] 0xfb:0xe DW_TAG_member
	.long	254                     ## DW_AT_name
	.long	595                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	6
	.byte	13                      ## Abbrev [13] 0x109:0xe DW_TAG_member
	.long	271                     ## DW_AT_name
	.long	606                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	13                      ## Abbrev [13] 0x117:0xe DW_TAG_member
	.long	329                     ## DW_AT_name
	.long	635                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	16
	.byte	13                      ## Abbrev [13] 0x125:0xe DW_TAG_member
	.long	381                     ## DW_AT_name
	.long	675                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	20
	.byte	13                      ## Abbrev [13] 0x133:0xe DW_TAG_member
	.long	409                     ## DW_AT_name
	.long	533                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	24
	.byte	13                      ## Abbrev [13] 0x141:0xe DW_TAG_member
	.long	417                     ## DW_AT_name
	.long	697                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	32
	.byte	13                      ## Abbrev [13] 0x14f:0xe DW_TAG_member
	.long	458                     ## DW_AT_name
	.long	719                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	40
	.byte	13                      ## Abbrev [13] 0x15d:0xe DW_TAG_member
	.long	471                     ## DW_AT_name
	.long	697                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	48
	.byte	13                      ## Abbrev [13] 0x16b:0xe DW_TAG_member
	.long	480                     ## DW_AT_name
	.long	719                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	56
	.byte	13                      ## Abbrev [13] 0x179:0xe DW_TAG_member
	.long	493                     ## DW_AT_name
	.long	697                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	64
	.byte	13                      ## Abbrev [13] 0x187:0xe DW_TAG_member
	.long	502                     ## DW_AT_name
	.long	719                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	72
	.byte	13                      ## Abbrev [13] 0x195:0xe DW_TAG_member
	.long	515                     ## DW_AT_name
	.long	697                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	80
	.byte	13                      ## Abbrev [13] 0x1a3:0xe DW_TAG_member
	.long	528                     ## DW_AT_name
	.long	719                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	88
	.byte	13                      ## Abbrev [13] 0x1b1:0xe DW_TAG_member
	.long	545                     ## DW_AT_name
	.long	726                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	96
	.byte	13                      ## Abbrev [13] 0x1bf:0xe DW_TAG_member
	.long	598                     ## DW_AT_name
	.long	766                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	104
	.byte	13                      ## Abbrev [13] 0x1cd:0xe DW_TAG_member
	.long	635                     ## DW_AT_name
	.long	788                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	112
	.byte	13                      ## Abbrev [13] 0x1db:0xe DW_TAG_member
	.long	675                     ## DW_AT_name
	.long	657                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	116
	.byte	13                      ## Abbrev [13] 0x1e9:0xe DW_TAG_member
	.long	684                     ## DW_AT_name
	.long	657                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	120
	.byte	13                      ## Abbrev [13] 0x1f7:0xe DW_TAG_member
	.long	691                     ## DW_AT_name
	.long	120                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	124
	.byte	13                      ## Abbrev [13] 0x205:0xf DW_TAG_member
	.long	701                     ## DW_AT_name
	.long	810                     ## DW_AT_type
	.byte	6                       ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	3                       ## DW_AT_data_member_location
	.byte	35
	.ascii	"\200\001"
	.byte	0                       ## End Of Children Mark
	.byte	4                       ## Abbrev [4] 0x215:0xb DW_TAG_typedef
	.long	544                     ## DW_AT_type
	.long	176                     ## DW_AT_name
	.byte	5                       ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x220:0xb DW_TAG_typedef
	.long	120                     ## DW_AT_type
	.long	182                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	57                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x22b:0xb DW_TAG_typedef
	.long	566                     ## DW_AT_type
	.long	205                     ## DW_AT_name
	.byte	7                       ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x236:0xb DW_TAG_typedef
	.long	577                     ## DW_AT_type
	.long	212                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	70                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x241:0xb DW_TAG_typedef
	.long	588                     ## DW_AT_type
	.long	228                     ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	43                      ## DW_AT_decl_line
	.byte	3                       ## Abbrev [3] 0x24c:0x7 DW_TAG_base_type
	.long	239                     ## DW_AT_name
	.byte	7                       ## DW_AT_encoding
	.byte	2                       ## DW_AT_byte_size
	.byte	4                       ## Abbrev [4] 0x253:0xb DW_TAG_typedef
	.long	577                     ## DW_AT_type
	.long	263                     ## DW_AT_name
	.byte	8                       ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x25e:0xb DW_TAG_typedef
	.long	617                     ## DW_AT_type
	.long	278                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	62                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x269:0xb DW_TAG_typedef
	.long	628                     ## DW_AT_type
	.long	295                     ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	47                      ## DW_AT_decl_line
	.byte	3                       ## Abbrev [3] 0x274:0x7 DW_TAG_base_type
	.long	306                     ## DW_AT_name
	.byte	7                       ## DW_AT_encoding
	.byte	8                       ## DW_AT_byte_size
	.byte	4                       ## Abbrev [4] 0x27b:0xb DW_TAG_typedef
	.long	646                     ## DW_AT_type
	.long	336                     ## DW_AT_name
	.byte	9                       ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x286:0xb DW_TAG_typedef
	.long	657                     ## DW_AT_type
	.long	342                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	75                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x291:0xb DW_TAG_typedef
	.long	668                     ## DW_AT_type
	.long	357                     ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	45                      ## DW_AT_decl_line
	.byte	3                       ## Abbrev [3] 0x29c:0x7 DW_TAG_base_type
	.long	368                     ## DW_AT_name
	.byte	7                       ## DW_AT_encoding
	.byte	4                       ## DW_AT_byte_size
	.byte	4                       ## Abbrev [4] 0x2a3:0xb DW_TAG_typedef
	.long	686                     ## DW_AT_type
	.long	388                     ## DW_AT_name
	.byte	10                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x2ae:0xb DW_TAG_typedef
	.long	657                     ## DW_AT_type
	.long	394                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	60                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x2b9:0xb DW_TAG_typedef
	.long	708                     ## DW_AT_type
	.long	426                     ## DW_AT_name
	.byte	11                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x2c4:0xb DW_TAG_typedef
	.long	719                     ## DW_AT_type
	.long	433                     ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	120                     ## DW_AT_decl_line
	.byte	3                       ## Abbrev [3] 0x2cf:0x7 DW_TAG_base_type
	.long	449                     ## DW_AT_name
	.byte	5                       ## DW_AT_encoding
	.byte	8                       ## DW_AT_byte_size
	.byte	4                       ## Abbrev [4] 0x2d6:0xb DW_TAG_typedef
	.long	737                     ## DW_AT_type
	.long	553                     ## DW_AT_name
	.byte	12                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x2e1:0xb DW_TAG_typedef
	.long	748                     ## DW_AT_type
	.long	559                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	71                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x2ec:0xb DW_TAG_typedef
	.long	759                     ## DW_AT_type
	.long	574                     ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	46                      ## DW_AT_decl_line
	.byte	3                       ## Abbrev [3] 0x2f7:0x7 DW_TAG_base_type
	.long	584                     ## DW_AT_name
	.byte	5                       ## DW_AT_encoding
	.byte	8                       ## DW_AT_byte_size
	.byte	4                       ## Abbrev [4] 0x2fe:0xb DW_TAG_typedef
	.long	777                     ## DW_AT_type
	.long	608                     ## DW_AT_name
	.byte	13                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x309:0xb DW_TAG_typedef
	.long	748                     ## DW_AT_type
	.long	617                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	55                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x314:0xb DW_TAG_typedef
	.long	799                     ## DW_AT_type
	.long	646                     ## DW_AT_name
	.byte	14                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0x31f:0xb DW_TAG_typedef
	.long	120                     ## DW_AT_type
	.long	656                     ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	56                      ## DW_AT_decl_line
	.byte	14                      ## Abbrev [14] 0x32a:0xc DW_TAG_array_type
	.long	748                     ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0x32f:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	2                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	16                      ## Abbrev [16] 0x336:0x7 DW_TAG_base_type
	.long	711                     ## DW_AT_name
	.byte	8                       ## DW_AT_byte_size
	.byte	7                       ## DW_AT_encoding
	.byte	17                      ## Abbrev [17] 0x33d:0x34 DW_TAG_subprogram
	.long	720                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	301                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	10                      ## Abbrev [10] 0x348:0xc DW_TAG_formal_parameter
	.long	728                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	301                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	18                      ## Abbrev [18] 0x354:0x1c DW_TAG_lexical_block
	.byte	11                      ## Abbrev [11] 0x355:0xc DW_TAG_variable
	.long	735                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	305                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	18                      ## Abbrev [18] 0x361:0xe DW_TAG_lexical_block
	.byte	11                      ## Abbrev [11] 0x362:0xc DW_TAG_variable
	.long	737                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	308                     ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	19                      ## Abbrev [19] 0x371:0x39 DW_TAG_subprogram
	.long	745                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	112                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	20                      ## Abbrev [20] 0x37b:0xb DW_TAG_formal_parameter
	.long	755                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	112                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0x386:0xb DW_TAG_formal_parameter
	.long	759                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	112                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0x391:0xb DW_TAG_formal_parameter
	.long	764                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	112                     ## DW_AT_decl_line
	.long	938                     ## DW_AT_type
	.byte	18                      ## Abbrev [18] 0x39c:0xd DW_TAG_lexical_block
	.byte	21                      ## Abbrev [21] 0x39d:0xb DW_TAG_variable
	.long	769                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	116                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0x3aa:0x5 DW_TAG_pointer_type
	.long	170                     ## DW_AT_type
	.byte	19                      ## Abbrev [19] 0x3af:0x67 DW_TAG_subprogram
	.long	771                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	138                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	20                      ## Abbrev [20] 0x3b9:0xb DW_TAG_formal_parameter
	.long	759                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	138                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0x3c4:0xb DW_TAG_formal_parameter
	.long	764                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	138                     ## DW_AT_decl_line
	.long	938                     ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x3cf:0xb DW_TAG_variable
	.long	786                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	147                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x3da:0xb DW_TAG_variable
	.long	791                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	146                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x3e5:0xb DW_TAG_variable
	.long	796                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	144                     ## DW_AT_decl_line
	.long	1046                    ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x3f0:0xb DW_TAG_variable
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	145                     ## DW_AT_decl_line
	.long	938                     ## DW_AT_type
	.byte	18                      ## Abbrev [18] 0x3fb:0x1a DW_TAG_lexical_block
	.byte	21                      ## Abbrev [21] 0x3fc:0xb DW_TAG_variable
	.long	769                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	151                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	18                      ## Abbrev [18] 0x407:0xd DW_TAG_lexical_block
	.byte	21                      ## Abbrev [21] 0x408:0xb DW_TAG_variable
	.long	806                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	153                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0x416:0x5 DW_TAG_pointer_type
	.long	938                     ## DW_AT_type
	.byte	17                      ## Abbrev [17] 0x41b:0x30 DW_TAG_subprogram
	.long	810                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	335                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	10                      ## Abbrev [10] 0x426:0xc DW_TAG_formal_parameter
	.long	823                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	335                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x432:0xc DW_TAG_variable
	.long	769                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	337                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x43e:0xc DW_TAG_variable
	.long	830                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	338                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	22                      ## Abbrev [22] 0x44b:0x25 DW_TAG_subprogram
	.long	832                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	232                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.long	69                      ## DW_AT_type
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	20                      ## Abbrev [20] 0x459:0xb DW_TAG_formal_parameter
	.long	735                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	232                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0x464:0xb DW_TAG_formal_parameter
	.long	843                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	232                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	19                      ## Abbrev [19] 0x470:0x16 DW_TAG_subprogram
	.long	845                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	179                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	20                      ## Abbrev [20] 0x47a:0xb DW_TAG_formal_parameter
	.long	857                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	179                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	19                      ## Abbrev [19] 0x486:0x3b DW_TAG_subprogram
	.long	863                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	123                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	20                      ## Abbrev [20] 0x490:0xb DW_TAG_formal_parameter
	.long	791                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	123                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0x49b:0xb DW_TAG_formal_parameter
	.long	796                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	123                     ## DW_AT_decl_line
	.long	1046                    ## DW_AT_type
	.byte	18                      ## Abbrev [18] 0x4a6:0x1a DW_TAG_lexical_block
	.byte	21                      ## Abbrev [21] 0x4a7:0xb DW_TAG_variable
	.long	769                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	126                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	18                      ## Abbrev [18] 0x4b2:0xd DW_TAG_lexical_block
	.byte	21                      ## Abbrev [21] 0x4b3:0xb DW_TAG_variable
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	129                     ## DW_AT_decl_line
	.long	938                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	19                      ## Abbrev [19] 0x4c1:0x2c DW_TAG_subprogram
	.long	877                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	85                      ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	20                      ## Abbrev [20] 0x4cb:0xb DW_TAG_formal_parameter
	.long	891                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	85                      ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0x4d6:0xb DW_TAG_formal_parameter
	.long	897                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	85                      ## DW_AT_decl_line
	.long	1046                    ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x4e1:0xb DW_TAG_variable
	.long	902                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	87                      ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	19                      ## Abbrev [19] 0x4ed:0x2c DW_TAG_subprogram
	.long	906                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	98                      ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	21                      ## Abbrev [21] 0x4f7:0xb DW_TAG_variable
	.long	923                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	100                     ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x502:0xb DW_TAG_variable
	.long	728                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	102                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x50d:0xb DW_TAG_variable
	.long	930                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	101                     ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	17                      ## Abbrev [17] 0x519:0x48 DW_TAG_subprogram
	.long	937                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	269                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	10                      ## Abbrev [10] 0x524:0xc DW_TAG_formal_parameter
	.long	948                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	269                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	10                      ## Abbrev [10] 0x530:0xc DW_TAG_formal_parameter
	.long	950                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	269                     ## DW_AT_decl_line
	.long	1377                    ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x53c:0xc DW_TAG_variable
	.long	962                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	273                     ## DW_AT_decl_line
	.long	1415                    ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x548:0xc DW_TAG_variable
	.long	769                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	271                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x554:0xc DW_TAG_variable
	.long	965                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	272                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0x561:0x5 DW_TAG_pointer_type
	.long	1382                    ## DW_AT_type
	.byte	12                      ## Abbrev [12] 0x566:0x17 DW_TAG_structure_type
	.long	954                     ## DW_AT_name
	.byte	8                       ## DW_AT_byte_size
	.byte	1                       ## DW_AT_decl_file
	.byte	213                     ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0x56e:0xe DW_TAG_member
	.long	764                     ## DW_AT_name
	.long	1405                    ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	215                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0x57d:0x5 DW_TAG_pointer_type
	.long	1410                    ## DW_AT_type
	.byte	7                       ## Abbrev [7] 0x582:0x5 DW_TAG_const_type
	.long	170                     ## DW_AT_type
	.byte	14                      ## Abbrev [14] 0x587:0xc DW_TAG_array_type
	.long	69                      ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0x58c:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	2                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	22                      ## Abbrev [22] 0x593:0x3b DW_TAG_subprogram
	.long	968                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	240                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.long	69                      ## DW_AT_type
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	20                      ## Abbrev [20] 0x5a1:0xb DW_TAG_formal_parameter
	.long	965                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	240                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0x5ac:0xb DW_TAG_formal_parameter
	.long	979                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	240                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0x5b7:0xb DW_TAG_formal_parameter
	.long	950                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	240                     ## DW_AT_decl_line
	.long	1377                    ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x5c2:0xb DW_TAG_variable
	.long	902                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	242                     ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	23                      ## Abbrev [23] 0x5ce:0x509 DW_TAG_subprogram
	.quad	Lfunc_begin0            ## DW_AT_low_pc
	.quad	Lfunc_end0              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	983                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	365                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.long	69                      ## DW_AT_type
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	24                      ## Abbrev [24] 0x5ef:0x10 DW_TAG_formal_parameter
Lset396 = Ldebug_loc0-Lsection_debug_loc ## DW_AT_location
	.long	Lset396
	.long	759                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	365                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	24                      ## Abbrev [24] 0x5ff:0x10 DW_TAG_formal_parameter
Lset397 = Ldebug_loc1-Lsection_debug_loc ## DW_AT_location
	.long	Lset397
	.long	764                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	365                     ## DW_AT_decl_line
	.long	938                     ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x60f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\240~"
	.long	1099                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	368                     ## DW_AT_decl_line
	.long	3349                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x61f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\240v"
	.long	1105                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	369                     ## DW_AT_decl_line
	.long	3361                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x62f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\240n"
	.long	1110                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	370                     ## DW_AT_decl_line
	.long	3361                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x63f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\230n"
	.long	962                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	380                     ## DW_AT_decl_line
	.long	1415                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x64f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\200n"
	.long	1116                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	381                     ## DW_AT_decl_line
	.long	3374                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x65f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\360m"
	.long	1125                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	382                     ## DW_AT_decl_line
	.long	3374                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x66f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\340m"
	.long	1130                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	383                     ## DW_AT_decl_line
	.long	3374                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x67f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\300m"
	.long	1140                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	384                     ## DW_AT_decl_line
	.long	3349                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x68f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\240m"
	.long	1145                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	397                     ## DW_AT_decl_line
	.long	3386                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x69f:0x10 DW_TAG_variable
Lset398 = Ldebug_loc2-Lsection_debug_loc ## DW_AT_location
	.long	Lset398
	.long	1150                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	379                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x6af:0x10 DW_TAG_variable
Lset399 = Ldebug_loc3-Lsection_debug_loc ## DW_AT_location
	.long	Lset399
	.long	1167                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	378                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x6bf:0x10 DW_TAG_variable
Lset400 = Ldebug_loc4-Lsection_debug_loc ## DW_AT_location
	.long	Lset400
	.long	769                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	375                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	27                      ## Abbrev [27] 0x6cf:0xd DW_TAG_variable
	.byte	0                       ## DW_AT_const_value
	.long	1180                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	372                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x6dc:0x10 DW_TAG_variable
Lset401 = Ldebug_loc5-Lsection_debug_loc ## DW_AT_location
	.long	Lset401
	.long	728                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	386                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x6ec:0x10 DW_TAG_variable
Lset402 = Ldebug_loc6-Lsection_debug_loc ## DW_AT_location
	.long	Lset402
	.long	1186                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	406                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	27                      ## Abbrev [27] 0x6fc:0xd DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	1196                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	392                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	27                      ## Abbrev [27] 0x709:0xd DW_TAG_variable
	.byte	0                       ## DW_AT_const_value
	.long	1200                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	389                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	27                      ## Abbrev [27] 0x716:0xe DW_TAG_variable
	.asciz	"\320"                  ## DW_AT_const_value
	.long	1204                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	387                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x724:0x10 DW_TAG_variable
Lset403 = Ldebug_loc7-Lsection_debug_loc ## DW_AT_location
	.long	Lset403
	.long	1208                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	401                     ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x734:0x10 DW_TAG_variable
Lset404 = Ldebug_loc8-Lsection_debug_loc ## DW_AT_location
	.long	Lset404
	.long	1217                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	407                     ## DW_AT_decl_line
	.long	3398                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x744:0x10 DW_TAG_variable
Lset405 = Ldebug_loc9-Lsection_debug_loc ## DW_AT_location
	.long	Lset405
	.long	1452                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	407                     ## DW_AT_decl_line
	.long	3398                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x754:0x10 DW_TAG_variable
Lset406 = Ldebug_loc10-Lsection_debug_loc ## DW_AT_location
	.long	Lset406
	.long	1456                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	404                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x764:0x10 DW_TAG_variable
Lset407 = Ldebug_loc11-Lsection_debug_loc ## DW_AT_location
	.long	Lset407
	.long	1466                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	405                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x774:0x10 DW_TAG_variable
Lset408 = Ldebug_loc12-Lsection_debug_loc ## DW_AT_location
	.long	Lset408
	.long	1477                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	403                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x784:0x10 DW_TAG_variable
Lset409 = Ldebug_loc13-Lsection_debug_loc ## DW_AT_location
	.long	Lset409
	.long	1481                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	374                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x794:0x10 DW_TAG_variable
Lset410 = Ldebug_loc14-Lsection_debug_loc ## DW_AT_location
	.long	Lset410
	.long	1488                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	391                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7a4:0x10 DW_TAG_variable
Lset411 = Ldebug_loc22-Lsection_debug_loc ## DW_AT_location
	.long	Lset411
	.long	1496                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	373                     ## DW_AT_decl_line
	.long	3761                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7b4:0x10 DW_TAG_variable
Lset412 = Ldebug_loc23-Lsection_debug_loc ## DW_AT_location
	.long	Lset412
	.long	1526                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	376                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7c4:0x10 DW_TAG_variable
Lset413 = Ldebug_loc24-Lsection_debug_loc ## DW_AT_location
	.long	Lset413
	.long	1535                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	394                     ## DW_AT_decl_line
	.long	3783                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7d4:0x10 DW_TAG_variable
Lset414 = Ldebug_loc25-Lsection_debug_loc ## DW_AT_location
	.long	Lset414
	.long	1631                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	395                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x7e4:0xc DW_TAG_variable
	.long	1639                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	398                     ## DW_AT_decl_line
	.long	3937                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7f0:0x10 DW_TAG_variable
Lset415 = Ldebug_loc26-Lsection_debug_loc ## DW_AT_location
	.long	Lset415
	.long	1694                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	400                     ## DW_AT_decl_line
	.long	3739                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x800:0x10 DW_TAG_variable
Lset416 = Ldebug_loc27-Lsection_debug_loc ## DW_AT_location
	.long	Lset416
	.long	1701                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	367                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x810:0xc DW_TAG_variable
	.long	1703                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	399                     ## DW_AT_decl_line
	.long	3937                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x81c:0x10 DW_TAG_variable
Lset417 = Ldebug_loc36-Lsection_debug_loc ## DW_AT_location
	.long	Lset417
	.long	1712                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	385                     ## DW_AT_decl_line
	.long	719                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x82c:0x10 DW_TAG_variable
Lset418 = Ldebug_loc39-Lsection_debug_loc ## DW_AT_location
	.long	Lset418
	.long	1717                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	402                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	27                      ## Abbrev [27] 0x83c:0xd DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	1728                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	393                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x849:0x10 DW_TAG_variable
Lset419 = Ldebug_loc40-Lsection_debug_loc ## DW_AT_location
	.long	Lset419
	.long	1730                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	390                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x859:0xc DW_TAG_variable
	.long	1734                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	371                     ## DW_AT_decl_line
	.long	3985                    ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x865:0xc DW_TAG_variable
	.long	1740                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	377                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x871:0xc DW_TAG_variable
	.long	843                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	388                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x87d:0xc DW_TAG_variable
	.long	950                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	396                     ## DW_AT_decl_line
	.long	3997                    ## DW_AT_type
	.byte	28                      ## Abbrev [28] 0x889:0x1f DW_TAG_inlined_subroutine
	.long	175                     ## DW_AT_abstract_origin
Lset420 = Ldebug_ranges0-Ldebug_range   ## DW_AT_ranges
	.long	Lset420
	.byte	1                       ## DW_AT_call_file
	.short	437                     ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0x895:0x9 DW_TAG_formal_parameter
Lset421 = Ldebug_loc15-Lsection_debug_loc ## DW_AT_location
	.long	Lset421
	.long	190                     ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0x89e:0x9 DW_TAG_variable
Lset422 = Ldebug_loc16-Lsection_debug_loc ## DW_AT_location
	.long	Lset422
	.long	202                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	28                      ## Abbrev [28] 0x8a8:0x31 DW_TAG_inlined_subroutine
	.long	829                     ## DW_AT_abstract_origin
Lset423 = Ldebug_ranges1-Ldebug_range   ## DW_AT_ranges
	.long	Lset423
	.byte	1                       ## DW_AT_call_file
	.short	461                     ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0x8b4:0x9 DW_TAG_formal_parameter
Lset424 = Ldebug_loc17-Lsection_debug_loc ## DW_AT_location
	.long	Lset424
	.long	840                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x8bd:0x1b DW_TAG_lexical_block
Lset425 = Ldebug_ranges3-Ldebug_range   ## DW_AT_ranges
	.long	Lset425
	.byte	32                      ## Abbrev [32] 0x8c2:0x6 DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	853                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x8c8:0xf DW_TAG_lexical_block
Lset426 = Ldebug_ranges2-Ldebug_range   ## DW_AT_ranges
	.long	Lset426
	.byte	30                      ## Abbrev [30] 0x8cd:0x9 DW_TAG_variable
Lset427 = Ldebug_loc18-Lsection_debug_loc ## DW_AT_location
	.long	Lset427
	.long	866                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	28                      ## Abbrev [28] 0x8d9:0x8e DW_TAG_inlined_subroutine
	.long	943                     ## DW_AT_abstract_origin
Lset428 = Ldebug_ranges4-Ldebug_range   ## DW_AT_ranges
	.long	Lset428
	.byte	1                       ## DW_AT_call_file
	.short	624                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0x8e5:0x9 DW_TAG_variable
Lset429 = Ldebug_loc28-Lsection_debug_loc ## DW_AT_location
	.long	Lset429
	.long	975                     ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0x8ee:0x9 DW_TAG_variable
Lset430 = Ldebug_loc29-Lsection_debug_loc ## DW_AT_location
	.long	Lset430
	.long	986                     ## DW_AT_abstract_origin
	.byte	33                      ## Abbrev [33] 0x8f7:0x18 DW_TAG_inlined_subroutine
	.long	881                     ## DW_AT_abstract_origin
Lset431 = Ldebug_ranges5-Ldebug_range   ## DW_AT_ranges
	.long	Lset431
	.byte	1                       ## DW_AT_call_file
	.byte	140                     ## DW_AT_call_line
	.byte	31                      ## Abbrev [31] 0x902:0xc DW_TAG_lexical_block
Lset432 = Ldebug_ranges6-Ldebug_range   ## DW_AT_ranges
	.long	Lset432
	.byte	32                      ## Abbrev [32] 0x907:0x6 DW_TAG_variable
	.byte	0                       ## DW_AT_const_value
	.long	925                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	31                      ## Abbrev [31] 0x90f:0x1b DW_TAG_lexical_block
Lset433 = Ldebug_ranges8-Ldebug_range   ## DW_AT_ranges
	.long	Lset433
	.byte	32                      ## Abbrev [32] 0x914:0x6 DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	1020                    ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x91a:0xf DW_TAG_lexical_block
Lset434 = Ldebug_ranges7-Ldebug_range   ## DW_AT_ranges
	.long	Lset434
	.byte	30                      ## Abbrev [30] 0x91f:0x9 DW_TAG_variable
Lset435 = Ldebug_loc30-Lsection_debug_loc ## DW_AT_location
	.long	Lset435
	.long	1032                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	33                      ## Abbrev [33] 0x92a:0x27 DW_TAG_inlined_subroutine
	.long	1158                    ## DW_AT_abstract_origin
Lset436 = Ldebug_ranges9-Ldebug_range   ## DW_AT_ranges
	.long	Lset436
	.byte	1                       ## DW_AT_call_file
	.byte	171                     ## DW_AT_call_line
	.byte	31                      ## Abbrev [31] 0x935:0x1b DW_TAG_lexical_block
Lset437 = Ldebug_ranges11-Ldebug_range  ## DW_AT_ranges
	.long	Lset437
	.byte	32                      ## Abbrev [32] 0x93a:0x6 DW_TAG_variable
	.byte	0                       ## DW_AT_const_value
	.long	1191                    ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x940:0xf DW_TAG_lexical_block
Lset438 = Ldebug_ranges10-Ldebug_range  ## DW_AT_ranges
	.long	Lset438
	.byte	30                      ## Abbrev [30] 0x945:0x9 DW_TAG_variable
Lset439 = Ldebug_loc31-Lsection_debug_loc ## DW_AT_location
	.long	Lset439
	.long	1203                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	33                      ## Abbrev [33] 0x951:0x15 DW_TAG_inlined_subroutine
	.long	1217                    ## DW_AT_abstract_origin
Lset440 = Ldebug_ranges12-Ldebug_range  ## DW_AT_ranges
	.long	Lset440
	.byte	1                       ## DW_AT_call_file
	.byte	172                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0x95c:0x9 DW_TAG_variable
Lset441 = Ldebug_loc32-Lsection_debug_loc ## DW_AT_location
	.long	Lset441
	.long	1249                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	34                      ## Abbrev [34] 0x967:0x18 DW_TAG_inlined_subroutine
	.long	1136                    ## DW_AT_abstract_origin
	.quad	Ltmp139                 ## DW_AT_low_pc
	.quad	Ltmp141                 ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	612                     ## DW_AT_call_line
	.byte	28                      ## Abbrev [28] 0x97f:0x28 DW_TAG_inlined_subroutine
	.long	1261                    ## DW_AT_abstract_origin
Lset442 = Ldebug_ranges13-Ldebug_range  ## DW_AT_ranges
	.long	Lset442
	.byte	1                       ## DW_AT_call_file
	.short	625                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0x98b:0x9 DW_TAG_variable
Lset443 = Ldebug_loc33-Lsection_debug_loc ## DW_AT_location
	.long	Lset443
	.long	1271                    ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0x994:0x9 DW_TAG_variable
Lset444 = Ldebug_loc34-Lsection_debug_loc ## DW_AT_location
	.long	Lset444
	.long	1282                    ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0x99d:0x9 DW_TAG_variable
Lset445 = Ldebug_loc35-Lsection_debug_loc ## DW_AT_location
	.long	Lset445
	.long	1293                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	31                      ## Abbrev [31] 0x9a7:0x44 DW_TAG_lexical_block
Lset446 = Ldebug_ranges17-Ldebug_range  ## DW_AT_ranges
	.long	Lset446
	.byte	27                      ## Abbrev [27] 0x9ac:0xd DW_TAG_variable
	.byte	0                       ## DW_AT_const_value
	.long	735                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	662                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	28                      ## Abbrev [28] 0x9b9:0x31 DW_TAG_inlined_subroutine
	.long	829                     ## DW_AT_abstract_origin
Lset447 = Ldebug_ranges14-Ldebug_range  ## DW_AT_ranges
	.long	Lset447
	.byte	1                       ## DW_AT_call_file
	.short	672                     ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0x9c5:0x9 DW_TAG_formal_parameter
Lset448 = Ldebug_loc37-Lsection_debug_loc ## DW_AT_location
	.long	Lset448
	.long	840                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x9ce:0x1b DW_TAG_lexical_block
Lset449 = Ldebug_ranges16-Ldebug_range  ## DW_AT_ranges
	.long	Lset449
	.byte	32                      ## Abbrev [32] 0x9d3:0x6 DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	853                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x9d9:0xf DW_TAG_lexical_block
Lset450 = Ldebug_ranges15-Ldebug_range  ## DW_AT_ranges
	.long	Lset450
	.byte	30                      ## Abbrev [30] 0x9de:0x9 DW_TAG_variable
Lset451 = Ldebug_loc38-Lsection_debug_loc ## DW_AT_location
	.long	Lset451
	.long	866                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	28                      ## Abbrev [28] 0x9eb:0x31 DW_TAG_inlined_subroutine
	.long	829                     ## DW_AT_abstract_origin
Lset452 = Ldebug_ranges18-Ldebug_range  ## DW_AT_ranges
	.long	Lset452
	.byte	1                       ## DW_AT_call_file
	.short	469                     ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0x9f7:0x9 DW_TAG_formal_parameter
Lset453 = Ldebug_loc19-Lsection_debug_loc ## DW_AT_location
	.long	Lset453
	.long	840                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0xa00:0x1b DW_TAG_lexical_block
Lset454 = Ldebug_ranges20-Ldebug_range  ## DW_AT_ranges
	.long	Lset454
	.byte	32                      ## Abbrev [32] 0xa05:0x6 DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	853                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0xa0b:0xf DW_TAG_lexical_block
Lset455 = Ldebug_ranges19-Ldebug_range  ## DW_AT_ranges
	.long	Lset455
	.byte	30                      ## Abbrev [30] 0xa10:0x9 DW_TAG_variable
Lset456 = Ldebug_loc20-Lsection_debug_loc ## DW_AT_location
	.long	Lset456
	.long	866                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	28                      ## Abbrev [28] 0xa1c:0x16 DW_TAG_inlined_subroutine
	.long	1051                    ## DW_AT_abstract_origin
Lset457 = Ldebug_ranges21-Ldebug_range  ## DW_AT_ranges
	.long	Lset457
	.byte	1                       ## DW_AT_call_file
	.short	471                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0xa28:0x9 DW_TAG_variable
Lset458 = Ldebug_loc21-Lsection_debug_loc ## DW_AT_location
	.long	Lset458
	.long	1074                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	34                      ## Abbrev [34] 0xa32:0x18 DW_TAG_inlined_subroutine
	.long	1099                    ## DW_AT_abstract_origin
	.quad	Ltmp79                  ## DW_AT_low_pc
	.quad	Ltmp80                  ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	472                     ## DW_AT_call_line
	.byte	35                      ## Abbrev [35] 0xa4a:0x1e DW_TAG_inlined_subroutine
	.long	1099                    ## DW_AT_abstract_origin
	.quad	Ltmp86                  ## DW_AT_low_pc
	.quad	Ltmp88                  ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	486                     ## DW_AT_call_line
	.byte	36                      ## Abbrev [36] 0xa62:0x5 DW_TAG_formal_parameter
	.long	1124                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	35                      ## Abbrev [35] 0xa68:0x1e DW_TAG_inlined_subroutine
	.long	1099                    ## DW_AT_abstract_origin
	.quad	Ltmp105                 ## DW_AT_low_pc
	.quad	Ltmp107                 ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	516                     ## DW_AT_call_line
	.byte	36                      ## Abbrev [36] 0xa80:0x5 DW_TAG_formal_parameter
	.long	1124                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	35                      ## Abbrev [35] 0xa86:0x50 DW_TAG_inlined_subroutine
	.long	1305                    ## DW_AT_abstract_origin
	.quad	Ltmp275                 ## DW_AT_low_pc
	.quad	Ltmp327                 ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	564                     ## DW_AT_call_line
	.byte	37                      ## Abbrev [37] 0xa9e:0x6 DW_TAG_formal_parameter
	.byte	4                       ## DW_AT_const_value
	.long	1316                    ## DW_AT_abstract_origin
	.byte	38                      ## Abbrev [38] 0xaa4:0x9 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\300~"
	.long	1340                    ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0xaad:0x9 DW_TAG_variable
Lset459 = Ldebug_loc41-Lsection_debug_loc ## DW_AT_location
	.long	Lset459
	.long	1352                    ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0xab6:0x9 DW_TAG_variable
Lset460 = Ldebug_loc42-Lsection_debug_loc ## DW_AT_location
	.long	Lset460
	.long	1364                    ## DW_AT_abstract_origin
	.byte	28                      ## Abbrev [28] 0xabf:0x16 DW_TAG_inlined_subroutine
	.long	1427                    ## DW_AT_abstract_origin
Lset461 = Ldebug_ranges22-Ldebug_range  ## DW_AT_ranges
	.long	Lset461
	.byte	1                       ## DW_AT_call_file
	.short	282                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0xacb:0x9 DW_TAG_variable
Lset462 = Ldebug_loc43-Lsection_debug_loc ## DW_AT_location
	.long	Lset462
	.long	1474                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	39                      ## Abbrev [39] 0xad7:0x55 DW_TAG_subprogram
	.quad	Lfunc_begin1            ## DW_AT_low_pc
	.quad	Lfunc_end1              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	988                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	358                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	40                      ## Abbrev [40] 0xaf3:0x10 DW_TAG_formal_parameter
	.byte	3                       ## DW_AT_location
	.byte	85
	.byte	147
	.byte	4
	.long	1747                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	358                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	40                      ## Abbrev [40] 0xb03:0xe DW_TAG_formal_parameter
	.byte	1                       ## DW_AT_location
	.byte	84
	.long	1753                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	358                     ## DW_AT_decl_line
	.long	4009                    ## DW_AT_type
	.byte	40                      ## Abbrev [40] 0xb11:0xe DW_TAG_formal_parameter
	.byte	1                       ## DW_AT_location
	.byte	81
	.long	1766                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	358                     ## DW_AT_decl_line
	.long	169                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0xb1f:0xc DW_TAG_variable
	.long	1769                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	360                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	41                      ## Abbrev [41] 0xb2c:0x49 DW_TAG_subprogram
	.quad	Lfunc_begin2            ## DW_AT_low_pc
	.quad	Lfunc_end2              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	999                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	219                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	42                      ## Abbrev [42] 0xb47:0xf DW_TAG_formal_parameter
Lset463 = Ldebug_loc44-Lsection_debug_loc ## DW_AT_location
	.long	Lset463
	.long	1891                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	219                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	43                      ## Abbrev [43] 0xb56:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	80
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.long	4025                    ## DW_AT_type
	.byte	44                      ## Abbrev [44] 0xb64:0xf DW_TAG_variable
Lset464 = Ldebug_loc45-Lsection_debug_loc ## DW_AT_location
	.long	Lset464
	.long	1895                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	221                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	45                      ## Abbrev [45] 0xb73:0x1 DW_TAG_unspecified_parameters
	.byte	0                       ## End Of Children Mark
	.byte	41                      ## Abbrev [41] 0xb75:0x3a DW_TAG_subprogram
	.quad	Lfunc_begin3            ## DW_AT_low_pc
	.quad	Lfunc_end3              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	1010                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	202                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	42                      ## Abbrev [42] 0xb90:0xf DW_TAG_formal_parameter
Lset465 = Ldebug_loc46-Lsection_debug_loc ## DW_AT_location
	.long	Lset465
	.long	1891                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	202                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	43                      ## Abbrev [43] 0xb9f:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	96
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	204                     ## DW_AT_decl_line
	.long	4025                    ## DW_AT_type
	.byte	45                      ## Abbrev [45] 0xbad:0x1 DW_TAG_unspecified_parameters
	.byte	0                       ## End Of Children Mark
	.byte	41                      ## Abbrev [41] 0xbaf:0x49 DW_TAG_subprogram
	.quad	Lfunc_begin4            ## DW_AT_low_pc
	.quad	Lfunc_end4              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	1022                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	184                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	42                      ## Abbrev [42] 0xbca:0xf DW_TAG_formal_parameter
Lset466 = Ldebug_loc47-Lsection_debug_loc ## DW_AT_location
	.long	Lset466
	.long	1891                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	184                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	42                      ## Abbrev [42] 0xbd9:0xf DW_TAG_formal_parameter
Lset467 = Ldebug_loc48-Lsection_debug_loc ## DW_AT_location
	.long	Lset467
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	184                     ## DW_AT_decl_line
	.long	4135                    ## DW_AT_type
	.byte	44                      ## Abbrev [44] 0xbe8:0xf DW_TAG_variable
Lset468 = Ldebug_loc49-Lsection_debug_loc ## DW_AT_location
	.long	Lset468
	.long	1895                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	186                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	41                      ## Abbrev [41] 0xbf8:0x36 DW_TAG_subprogram
	.quad	Lfunc_begin5            ## DW_AT_low_pc
	.quad	Lfunc_end5              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	1035                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	194                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	20                      ## Abbrev [20] 0xc13:0xb DW_TAG_formal_parameter
	.long	1891                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	194                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	43                      ## Abbrev [43] 0xc1e:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	80
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	196                     ## DW_AT_decl_line
	.long	4025                    ## DW_AT_type
	.byte	45                      ## Abbrev [45] 0xc2c:0x1 DW_TAG_unspecified_parameters
	.byte	0                       ## End Of Children Mark
	.byte	19                      ## Abbrev [19] 0xc2e:0x2c DW_TAG_subprogram
	.long	1047                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	20                      ## Abbrev [20] 0xc38:0xb DW_TAG_formal_parameter
	.long	891                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0xc43:0xb DW_TAG_formal_parameter
	.long	897                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.long	1046                    ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0xc4e:0xb DW_TAG_formal_parameter
	.long	1065                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.long	3162                    ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xc5a:0x5 DW_TAG_pointer_type
	.long	69                      ## DW_AT_type
	.byte	41                      ## Abbrev [41] 0xc5f:0x9c DW_TAG_subprogram
	.quad	Lfunc_begin6            ## DW_AT_low_pc
	.quad	Lfunc_end6              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	1072                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	47                      ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	42                      ## Abbrev [42] 0xc7a:0xf DW_TAG_formal_parameter
Lset469 = Ldebug_loc50-Lsection_debug_loc ## DW_AT_location
	.long	Lset469
	.long	891                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	47                      ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	42                      ## Abbrev [42] 0xc89:0xf DW_TAG_formal_parameter
Lset470 = Ldebug_loc51-Lsection_debug_loc ## DW_AT_location
	.long	Lset470
	.long	897                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	47                      ## DW_AT_decl_line
	.long	1046                    ## DW_AT_type
	.byte	46                      ## Abbrev [46] 0xc98:0x62 DW_TAG_lexical_block
	.quad	Ltmp395                 ## DW_AT_low_pc
	.quad	Ltmp406                 ## DW_AT_high_pc
	.byte	43                      ## Abbrev [43] 0xca9:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	96
	.long	1902                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	53                      ## DW_AT_decl_line
	.long	4140                    ## DW_AT_type
	.byte	44                      ## Abbrev [44] 0xcb7:0xf DW_TAG_variable
Lset471 = Ldebug_loc53-Lsection_debug_loc ## DW_AT_location
	.long	Lset471
	.long	902                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	52                      ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	47                      ## Abbrev [47] 0xcc6:0x33 DW_TAG_inlined_subroutine
	.long	3118                    ## DW_AT_abstract_origin
	.quad	Ltmp403                 ## DW_AT_low_pc
	.quad	Ltmp405                 ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.byte	61                      ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0xcdd:0x9 DW_TAG_formal_parameter
Lset472 = Ldebug_loc54-Lsection_debug_loc ## DW_AT_location
	.long	Lset472
	.long	3128                    ## DW_AT_abstract_origin
	.byte	29                      ## Abbrev [29] 0xce6:0x9 DW_TAG_formal_parameter
Lset473 = Ldebug_loc55-Lsection_debug_loc ## DW_AT_location
	.long	Lset473
	.long	3139                    ## DW_AT_abstract_origin
	.byte	29                      ## Abbrev [29] 0xcef:0x9 DW_TAG_formal_parameter
Lset474 = Ldebug_loc52-Lsection_debug_loc ## DW_AT_location
	.long	Lset474
	.long	3150                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	48                      ## Abbrev [48] 0xcfb:0x1a DW_TAG_subprogram
	.long	1089                    ## DW_AT_name
	.byte	15                      ## DW_AT_decl_file
	.byte	114                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.long	69                      ## DW_AT_type
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	20                      ## Abbrev [20] 0xd09:0xb DW_TAG_formal_parameter
	.long	1913                    ## DW_AT_name
	.byte	15                      ## DW_AT_decl_file
	.byte	114                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xd15:0xc DW_TAG_array_type
	.long	170                     ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xd1a:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	4                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xd21:0xd DW_TAG_array_type
	.long	162                     ## DW_AT_type
	.byte	49                      ## Abbrev [49] 0xd26:0x7 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.short	1024                    ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xd2e:0xc DW_TAG_array_type
	.long	170                     ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xd33:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	2                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xd3a:0xc DW_TAG_array_type
	.long	1382                    ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xd3f:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	4                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	50                      ## Abbrev [50] 0xd46:0x37 DW_TAG_structure_type
	.long	1220                    ## DW_AT_name
	.byte	16                      ## DW_AT_byte_size
	.byte	16                      ## DW_AT_decl_file
	.short	286                     ## DW_AT_decl_line
	.byte	51                      ## Abbrev [51] 0xd4f:0xf DW_TAG_member
	.long	1230                    ## DW_AT_name
	.long	3453                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	287                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	51                      ## Abbrev [51] 0xd5e:0xf DW_TAG_member
	.long	1408                    ## DW_AT_name
	.long	3739                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	288                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	51                      ## Abbrev [51] 0xd6d:0xf DW_TAG_member
	.long	1443                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	289                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	12
	.byte	0                       ## End Of Children Mark
	.byte	52                      ## Abbrev [52] 0xd7d:0x28 DW_TAG_union_type
	.long	1230                    ## DW_AT_name
	.byte	8                       ## DW_AT_byte_size
	.byte	16                      ## DW_AT_decl_file
	.short	269                     ## DW_AT_decl_line
	.byte	51                      ## Abbrev [51] 0xd86:0xf DW_TAG_member
	.long	1244                    ## DW_AT_name
	.long	3493                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	270                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	51                      ## Abbrev [51] 0xd95:0xf DW_TAG_member
	.long	1257                    ## DW_AT_name
	.long	3506                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	271                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xda5:0x5 DW_TAG_pointer_type
	.long	3498                    ## DW_AT_type
	.byte	53                      ## Abbrev [53] 0xdaa:0x8 DW_TAG_subroutine_type
	.byte	1                       ## DW_AT_prototyped
	.byte	54                      ## Abbrev [54] 0xdac:0x5 DW_TAG_formal_parameter
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xdb2:0x5 DW_TAG_pointer_type
	.long	3511                    ## DW_AT_type
	.byte	53                      ## Abbrev [53] 0xdb7:0x12 DW_TAG_subroutine_type
	.byte	1                       ## DW_AT_prototyped
	.byte	54                      ## Abbrev [54] 0xdb9:0x5 DW_TAG_formal_parameter
	.long	69                      ## DW_AT_type
	.byte	54                      ## Abbrev [54] 0xdbe:0x5 DW_TAG_formal_parameter
	.long	3529                    ## DW_AT_type
	.byte	54                      ## Abbrev [54] 0xdc3:0x5 DW_TAG_formal_parameter
	.long	169                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xdc9:0x5 DW_TAG_pointer_type
	.long	3534                    ## DW_AT_type
	.byte	12                      ## Abbrev [12] 0xdce:0x95 DW_TAG_structure_type
	.long	1272                    ## DW_AT_name
	.byte	104                     ## DW_AT_byte_size
	.byte	16                      ## DW_AT_decl_file
	.byte	177                     ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xdd6:0xe DW_TAG_member
	.long	1282                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	178                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xde4:0xe DW_TAG_member
	.long	1291                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	179                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	13                      ## Abbrev [13] 0xdf2:0xe DW_TAG_member
	.long	1300                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	180                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	13                      ## Abbrev [13] 0xe00:0xe DW_TAG_member
	.long	1308                    ## DW_AT_name
	.long	98                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	181                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	12
	.byte	13                      ## Abbrev [13] 0xe0e:0xe DW_TAG_member
	.long	1315                    ## DW_AT_name
	.long	635                     ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	16
	.byte	13                      ## Abbrev [13] 0xe1c:0xe DW_TAG_member
	.long	1322                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	183                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	20
	.byte	13                      ## Abbrev [13] 0xe2a:0xe DW_TAG_member
	.long	1332                    ## DW_AT_name
	.long	169                     ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	184                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	24
	.byte	13                      ## Abbrev [13] 0xe38:0xe DW_TAG_member
	.long	1340                    ## DW_AT_name
	.long	3683                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	185                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	32
	.byte	13                      ## Abbrev [13] 0xe46:0xe DW_TAG_member
	.long	1376                    ## DW_AT_name
	.long	719                     ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	186                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	40
	.byte	13                      ## Abbrev [13] 0xe54:0xe DW_TAG_member
	.long	1384                    ## DW_AT_name
	.long	3720                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	187                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	48
	.byte	0                       ## End Of Children Mark
	.byte	55                      ## Abbrev [55] 0xe63:0x25 DW_TAG_union_type
	.long	1349                    ## DW_AT_name
	.byte	8                       ## DW_AT_byte_size
	.byte	16                      ## DW_AT_decl_file
	.byte	158                     ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xe6b:0xe DW_TAG_member
	.long	1356                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	160                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xe79:0xe DW_TAG_member
	.long	1366                    ## DW_AT_name
	.long	169                     ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	161                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xe88:0xc DW_TAG_array_type
	.long	3732                    ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xe8d:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	7                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	3                       ## Abbrev [3] 0xe94:0x7 DW_TAG_base_type
	.long	1390                    ## DW_AT_name
	.byte	7                       ## DW_AT_encoding
	.byte	8                       ## DW_AT_byte_size
	.byte	4                       ## Abbrev [4] 0xe9b:0xb DW_TAG_typedef
	.long	3750                    ## DW_AT_type
	.long	1416                    ## DW_AT_name
	.byte	17                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xea6:0xb DW_TAG_typedef
	.long	657                     ## DW_AT_type
	.long	1425                    ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	73                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xeb1:0xb DW_TAG_typedef
	.long	3772                    ## DW_AT_type
	.long	1503                    ## DW_AT_name
	.byte	18                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xebc:0xb DW_TAG_typedef
	.long	3732                    ## DW_AT_type
	.long	1510                    ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	92                      ## DW_AT_decl_line
	.byte	6                       ## Abbrev [6] 0xec7:0x5 DW_TAG_pointer_type
	.long	3788                    ## DW_AT_type
	.byte	12                      ## Abbrev [12] 0xecc:0x95 DW_TAG_structure_type
	.long	1538                    ## DW_AT_name
	.byte	72                      ## DW_AT_byte_size
	.byte	19                      ## DW_AT_decl_file
	.byte	84                      ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xed4:0xe DW_TAG_member
	.long	1545                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	85                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xee2:0xe DW_TAG_member
	.long	1553                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	86                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	13                      ## Abbrev [13] 0xef0:0xe DW_TAG_member
	.long	1563                    ## DW_AT_name
	.long	635                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	87                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	16
	.byte	13                      ## Abbrev [13] 0xefe:0xe DW_TAG_member
	.long	1570                    ## DW_AT_name
	.long	675                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	88                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	20
	.byte	13                      ## Abbrev [13] 0xf0c:0xe DW_TAG_member
	.long	1577                    ## DW_AT_name
	.long	708                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	89                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	24
	.byte	13                      ## Abbrev [13] 0xf1a:0xe DW_TAG_member
	.long	1587                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	90                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	32
	.byte	13                      ## Abbrev [13] 0xf28:0xe DW_TAG_member
	.long	1596                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	91                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	40
	.byte	13                      ## Abbrev [13] 0xf36:0xe DW_TAG_member
	.long	1605                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	92                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	48
	.byte	13                      ## Abbrev [13] 0xf44:0xe DW_TAG_member
	.long	1612                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	93                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	56
	.byte	13                      ## Abbrev [13] 0xf52:0xe DW_TAG_member
	.long	1621                    ## DW_AT_name
	.long	708                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	94                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	64
	.byte	0                       ## End Of Children Mark
	.byte	12                      ## Abbrev [12] 0xf61:0x25 DW_TAG_structure_type
	.long	1650                    ## DW_AT_name
	.byte	16                      ## DW_AT_byte_size
	.byte	20                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xf69:0xe DW_TAG_member
	.long	1658                    ## DW_AT_name
	.long	708                     ## DW_AT_type
	.byte	20                      ## DW_AT_decl_file
	.byte	32                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xf77:0xe DW_TAG_member
	.long	1665                    ## DW_AT_name
	.long	3974                    ## DW_AT_type
	.byte	20                      ## DW_AT_decl_file
	.byte	33                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	0                       ## End Of Children Mark
	.byte	4                       ## Abbrev [4] 0xf86:0xb DW_TAG_typedef
	.long	120                     ## DW_AT_type
	.long	1673                    ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.byte	14                      ## Abbrev [14] 0xf91:0xc DW_TAG_array_type
	.long	170                     ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xf96:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	100                     ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xf9d:0xc DW_TAG_array_type
	.long	1382                    ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xfa2:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	3                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xfa9:0x5 DW_TAG_pointer_type
	.long	4014                    ## DW_AT_type
	.byte	4                       ## Abbrev [4] 0xfae:0xb DW_TAG_typedef
	.long	3534                    ## DW_AT_type
	.long	1756                    ## DW_AT_name
	.byte	16                      ## DW_AT_decl_file
	.byte	188                     ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xfb9:0xb DW_TAG_typedef
	.long	4036                    ## DW_AT_type
	.long	1782                    ## DW_AT_name
	.byte	21                      ## DW_AT_decl_file
	.byte	31                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xfc4:0xb DW_TAG_typedef
	.long	4047                    ## DW_AT_type
	.long	1790                    ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	98                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xfcf:0xb DW_TAG_typedef
	.long	4058                    ## DW_AT_type
	.long	1807                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	14                      ## Abbrev [14] 0xfda:0xc DW_TAG_array_type
	.long	4070                    ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xfdf:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	1                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	12                      ## Abbrev [12] 0xfe6:0x41 DW_TAG_structure_type
	.long	1825                    ## DW_AT_name
	.byte	24                      ## DW_AT_byte_size
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xfee:0xe DW_TAG_member
	.long	1839                    ## DW_AT_name
	.long	668                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xffc:0xe DW_TAG_member
	.long	1849                    ## DW_AT_name
	.long	668                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	13                      ## Abbrev [13] 0x100a:0xe DW_TAG_member
	.long	1859                    ## DW_AT_name
	.long	169                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	13                      ## Abbrev [13] 0x1018:0xe DW_TAG_member
	.long	1877                    ## DW_AT_name
	.long	169                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	16
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0x1027:0x5 DW_TAG_pointer_type
	.long	4070                    ## DW_AT_type
	.byte	4                       ## Abbrev [4] 0x102c:0xb DW_TAG_typedef
	.long	1415                    ## DW_AT_type
	.long	1908                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	41                      ## DW_AT_decl_line
	.byte	0                       ## End Of Children Mark
	.section	__DWARF,__debug_ranges,regular,debug
Ldebug_range:
Ldebug_ranges0:
Lset475 = Ltmp33-Lfunc_begin0
	.quad	Lset475
Lset476 = Ltmp34-Lfunc_begin0
	.quad	Lset476
Lset477 = Ltmp35-Lfunc_begin0
	.quad	Lset477
Lset478 = Ltmp36-Lfunc_begin0
	.quad	Lset478
	.quad	0
	.quad	0
Ldebug_ranges1:
Lset479 = Ltmp44-Lfunc_begin0
	.quad	Lset479
Lset480 = Ltmp45-Lfunc_begin0
	.quad	Lset480
Lset481 = Ltmp50-Lfunc_begin0
	.quad	Lset481
Lset482 = Ltmp56-Lfunc_begin0
	.quad	Lset482
Lset483 = Ltmp63-Lfunc_begin0
	.quad	Lset483
Lset484 = Ltmp64-Lfunc_begin0
	.quad	Lset484
Lset485 = Ltmp109-Lfunc_begin0
	.quad	Lset485
Lset486 = Ltmp110-Lfunc_begin0
	.quad	Lset486
Lset487 = Ltmp227-Lfunc_begin0
	.quad	Lset487
Lset488 = Ltmp228-Lfunc_begin0
	.quad	Lset488
Lset489 = Ltmp233-Lfunc_begin0
	.quad	Lset489
Lset490 = Ltmp234-Lfunc_begin0
	.quad	Lset490
Lset491 = Ltmp240-Lfunc_begin0
	.quad	Lset491
Lset492 = Ltmp241-Lfunc_begin0
	.quad	Lset492
	.quad	0
	.quad	0
Ldebug_ranges2:
Lset493 = Ltmp44-Lfunc_begin0
	.quad	Lset493
Lset494 = Ltmp45-Lfunc_begin0
	.quad	Lset494
Lset495 = Ltmp50-Lfunc_begin0
	.quad	Lset495
Lset496 = Ltmp56-Lfunc_begin0
	.quad	Lset496
Lset497 = Ltmp63-Lfunc_begin0
	.quad	Lset497
Lset498 = Ltmp64-Lfunc_begin0
	.quad	Lset498
Lset499 = Ltmp109-Lfunc_begin0
	.quad	Lset499
Lset500 = Ltmp110-Lfunc_begin0
	.quad	Lset500
Lset501 = Ltmp227-Lfunc_begin0
	.quad	Lset501
Lset502 = Ltmp228-Lfunc_begin0
	.quad	Lset502
Lset503 = Ltmp233-Lfunc_begin0
	.quad	Lset503
Lset504 = Ltmp234-Lfunc_begin0
	.quad	Lset504
Lset505 = Ltmp240-Lfunc_begin0
	.quad	Lset505
Lset506 = Ltmp241-Lfunc_begin0
	.quad	Lset506
	.quad	0
	.quad	0
Ldebug_ranges3:
Lset507 = Ltmp44-Lfunc_begin0
	.quad	Lset507
Lset508 = Ltmp45-Lfunc_begin0
	.quad	Lset508
Lset509 = Ltmp50-Lfunc_begin0
	.quad	Lset509
Lset510 = Ltmp56-Lfunc_begin0
	.quad	Lset510
Lset511 = Ltmp63-Lfunc_begin0
	.quad	Lset511
Lset512 = Ltmp64-Lfunc_begin0
	.quad	Lset512
Lset513 = Ltmp109-Lfunc_begin0
	.quad	Lset513
Lset514 = Ltmp110-Lfunc_begin0
	.quad	Lset514
Lset515 = Ltmp227-Lfunc_begin0
	.quad	Lset515
Lset516 = Ltmp228-Lfunc_begin0
	.quad	Lset516
Lset517 = Ltmp233-Lfunc_begin0
	.quad	Lset517
Lset518 = Ltmp234-Lfunc_begin0
	.quad	Lset518
Lset519 = Ltmp240-Lfunc_begin0
	.quad	Lset519
Lset520 = Ltmp241-Lfunc_begin0
	.quad	Lset520
	.quad	0
	.quad	0
Ldebug_ranges4:
Lset521 = Ltmp45-Lfunc_begin0
	.quad	Lset521
Lset522 = Ltmp46-Lfunc_begin0
	.quad	Lset522
Lset523 = Ltmp110-Lfunc_begin0
	.quad	Lset523
Lset524 = Ltmp111-Lfunc_begin0
	.quad	Lset524
Lset525 = Ltmp150-Lfunc_begin0
	.quad	Lset525
Lset526 = Ltmp202-Lfunc_begin0
	.quad	Lset526
Lset527 = Ltmp203-Lfunc_begin0
	.quad	Lset527
Lset528 = Ltmp207-Lfunc_begin0
	.quad	Lset528
Lset529 = Ltmp208-Lfunc_begin0
	.quad	Lset529
Lset530 = Ltmp210-Lfunc_begin0
	.quad	Lset530
Lset531 = Ltmp245-Lfunc_begin0
	.quad	Lset531
Lset532 = Ltmp246-Lfunc_begin0
	.quad	Lset532
Lset533 = Ltmp252-Lfunc_begin0
	.quad	Lset533
Lset534 = Ltmp256-Lfunc_begin0
	.quad	Lset534
Lset535 = Ltmp264-Lfunc_begin0
	.quad	Lset535
Lset536 = Ltmp268-Lfunc_begin0
	.quad	Lset536
	.quad	0
	.quad	0
Ldebug_ranges5:
Lset537 = Ltmp45-Lfunc_begin0
	.quad	Lset537
Lset538 = Ltmp46-Lfunc_begin0
	.quad	Lset538
Lset539 = Ltmp110-Lfunc_begin0
	.quad	Lset539
Lset540 = Ltmp111-Lfunc_begin0
	.quad	Lset540
Lset541 = Ltmp150-Lfunc_begin0
	.quad	Lset541
Lset542 = Ltmp158-Lfunc_begin0
	.quad	Lset542
Lset543 = Ltmp188-Lfunc_begin0
	.quad	Lset543
Lset544 = Ltmp189-Lfunc_begin0
	.quad	Lset544
Lset545 = Ltmp192-Lfunc_begin0
	.quad	Lset545
Lset546 = Ltmp193-Lfunc_begin0
	.quad	Lset546
Lset547 = Ltmp197-Lfunc_begin0
	.quad	Lset547
Lset548 = Ltmp198-Lfunc_begin0
	.quad	Lset548
Lset549 = Ltmp245-Lfunc_begin0
	.quad	Lset549
Lset550 = Ltmp246-Lfunc_begin0
	.quad	Lset550
	.quad	0
	.quad	0
Ldebug_ranges6:
Lset551 = Ltmp45-Lfunc_begin0
	.quad	Lset551
Lset552 = Ltmp46-Lfunc_begin0
	.quad	Lset552
Lset553 = Ltmp110-Lfunc_begin0
	.quad	Lset553
Lset554 = Ltmp111-Lfunc_begin0
	.quad	Lset554
Lset555 = Ltmp152-Lfunc_begin0
	.quad	Lset555
Lset556 = Ltmp156-Lfunc_begin0
	.quad	Lset556
Lset557 = Ltmp188-Lfunc_begin0
	.quad	Lset557
Lset558 = Ltmp189-Lfunc_begin0
	.quad	Lset558
Lset559 = Ltmp245-Lfunc_begin0
	.quad	Lset559
Lset560 = Ltmp246-Lfunc_begin0
	.quad	Lset560
	.quad	0
	.quad	0
Ldebug_ranges7:
Lset561 = Ltmp162-Lfunc_begin0
	.quad	Lset561
Lset562 = Ltmp177-Lfunc_begin0
	.quad	Lset562
Lset563 = Ltmp252-Lfunc_begin0
	.quad	Lset563
Lset564 = Ltmp256-Lfunc_begin0
	.quad	Lset564
	.quad	0
	.quad	0
Ldebug_ranges8:
Lset565 = Ltmp161-Lfunc_begin0
	.quad	Lset565
Lset566 = Ltmp179-Lfunc_begin0
	.quad	Lset566
Lset567 = Ltmp252-Lfunc_begin0
	.quad	Lset567
Lset568 = Ltmp256-Lfunc_begin0
	.quad	Lset568
	.quad	0
	.quad	0
Ldebug_ranges9:
Lset569 = Ltmp181-Lfunc_begin0
	.quad	Lset569
Lset570 = Ltmp188-Lfunc_begin0
	.quad	Lset570
Lset571 = Ltmp189-Lfunc_begin0
	.quad	Lset571
Lset572 = Ltmp192-Lfunc_begin0
	.quad	Lset572
Lset573 = Ltmp193-Lfunc_begin0
	.quad	Lset573
Lset574 = Ltmp197-Lfunc_begin0
	.quad	Lset574
Lset575 = Ltmp198-Lfunc_begin0
	.quad	Lset575
Lset576 = Ltmp199-Lfunc_begin0
	.quad	Lset576
	.quad	0
	.quad	0
Ldebug_ranges10:
Lset577 = Ltmp185-Lfunc_begin0
	.quad	Lset577
Lset578 = Ltmp188-Lfunc_begin0
	.quad	Lset578
Lset579 = Ltmp189-Lfunc_begin0
	.quad	Lset579
Lset580 = Ltmp192-Lfunc_begin0
	.quad	Lset580
Lset581 = Ltmp193-Lfunc_begin0
	.quad	Lset581
Lset582 = Ltmp194-Lfunc_begin0
	.quad	Lset582
	.quad	0
	.quad	0
Ldebug_ranges11:
Lset583 = Ltmp183-Lfunc_begin0
	.quad	Lset583
Lset584 = Ltmp188-Lfunc_begin0
	.quad	Lset584
Lset585 = Ltmp189-Lfunc_begin0
	.quad	Lset585
Lset586 = Ltmp192-Lfunc_begin0
	.quad	Lset586
Lset587 = Ltmp193-Lfunc_begin0
	.quad	Lset587
Lset588 = Ltmp195-Lfunc_begin0
	.quad	Lset588
	.quad	0
	.quad	0
Ldebug_ranges12:
Lset589 = Ltmp199-Lfunc_begin0
	.quad	Lset589
Lset590 = Ltmp202-Lfunc_begin0
	.quad	Lset590
Lset591 = Ltmp203-Lfunc_begin0
	.quad	Lset591
Lset592 = Ltmp207-Lfunc_begin0
	.quad	Lset592
Lset593 = Ltmp266-Lfunc_begin0
	.quad	Lset593
Lset594 = Ltmp268-Lfunc_begin0
	.quad	Lset594
	.quad	0
	.quad	0
Ldebug_ranges13:
Lset595 = Ltmp202-Lfunc_begin0
	.quad	Lset595
Lset596 = Ltmp203-Lfunc_begin0
	.quad	Lset596
Lset597 = Ltmp207-Lfunc_begin0
	.quad	Lset597
Lset598 = Ltmp208-Lfunc_begin0
	.quad	Lset598
Lset599 = Ltmp210-Lfunc_begin0
	.quad	Lset599
Lset600 = Ltmp219-Lfunc_begin0
	.quad	Lset600
Lset601 = Ltmp258-Lfunc_begin0
	.quad	Lset601
Lset602 = Ltmp259-Lfunc_begin0
	.quad	Lset602
	.quad	0
	.quad	0
Ldebug_ranges14:
Lset603 = Ltmp238-Lfunc_begin0
	.quad	Lset603
Lset604 = Ltmp240-Lfunc_begin0
	.quad	Lset604
Lset605 = Ltmp241-Lfunc_begin0
	.quad	Lset605
Lset606 = Ltmp245-Lfunc_begin0
	.quad	Lset606
	.quad	0
	.quad	0
Ldebug_ranges15:
Lset607 = Ltmp238-Lfunc_begin0
	.quad	Lset607
Lset608 = Ltmp240-Lfunc_begin0
	.quad	Lset608
Lset609 = Ltmp241-Lfunc_begin0
	.quad	Lset609
Lset610 = Ltmp245-Lfunc_begin0
	.quad	Lset610
	.quad	0
	.quad	0
Ldebug_ranges16:
Lset611 = Ltmp238-Lfunc_begin0
	.quad	Lset611
Lset612 = Ltmp240-Lfunc_begin0
	.quad	Lset612
Lset613 = Ltmp241-Lfunc_begin0
	.quad	Lset613
Lset614 = Ltmp245-Lfunc_begin0
	.quad	Lset614
	.quad	0
	.quad	0
Ldebug_ranges17:
Lset615 = Ltmp234-Lfunc_begin0
	.quad	Lset615
Lset616 = Ltmp240-Lfunc_begin0
	.quad	Lset616
Lset617 = Ltmp241-Lfunc_begin0
	.quad	Lset617
Lset618 = Ltmp245-Lfunc_begin0
	.quad	Lset618
	.quad	0
	.quad	0
Ldebug_ranges18:
Lset619 = Ltmp61-Lfunc_begin0
	.quad	Lset619
Lset620 = Ltmp63-Lfunc_begin0
	.quad	Lset620
Lset621 = Ltmp64-Lfunc_begin0
	.quad	Lset621
Lset622 = Ltmp68-Lfunc_begin0
	.quad	Lset622
	.quad	0
	.quad	0
Ldebug_ranges19:
Lset623 = Ltmp61-Lfunc_begin0
	.quad	Lset623
Lset624 = Ltmp63-Lfunc_begin0
	.quad	Lset624
Lset625 = Ltmp64-Lfunc_begin0
	.quad	Lset625
Lset626 = Ltmp68-Lfunc_begin0
	.quad	Lset626
	.quad	0
	.quad	0
Ldebug_ranges20:
Lset627 = Ltmp61-Lfunc_begin0
	.quad	Lset627
Lset628 = Ltmp63-Lfunc_begin0
	.quad	Lset628
Lset629 = Ltmp64-Lfunc_begin0
	.quad	Lset629
Lset630 = Ltmp68-Lfunc_begin0
	.quad	Lset630
	.quad	0
	.quad	0
Ldebug_ranges21:
Lset631 = Ltmp70-Lfunc_begin0
	.quad	Lset631
Lset632 = Ltmp71-Lfunc_begin0
	.quad	Lset632
Lset633 = Ltmp73-Lfunc_begin0
	.quad	Lset633
Lset634 = Ltmp79-Lfunc_begin0
	.quad	Lset634
	.quad	0
	.quad	0
Ldebug_ranges22:
Lset635 = Ltmp278-Lfunc_begin0
	.quad	Lset635
Lset636 = Ltmp287-Lfunc_begin0
	.quad	Lset636
Lset637 = Ltmp293-Lfunc_begin0
	.quad	Lset637
Lset638 = Ltmp294-Lfunc_begin0
	.quad	Lset638
Lset639 = Ltmp300-Lfunc_begin0
	.quad	Lset639
Lset640 = Ltmp304-Lfunc_begin0
	.quad	Lset640
Lset641 = Ltmp306-Lfunc_begin0
	.quad	Lset641
Lset642 = Ltmp307-Lfunc_begin0
	.quad	Lset642
Lset643 = Ltmp308-Lfunc_begin0
	.quad	Lset643
Lset644 = Ltmp314-Lfunc_begin0
	.quad	Lset644
Lset645 = Ltmp315-Lfunc_begin0
	.quad	Lset645
Lset646 = Ltmp320-Lfunc_begin0
	.quad	Lset646
	.quad	0
	.quad	0
	.section	__DWARF,__apple_names,regular,debug
Lnames_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	11                      ## Header Bucket Count
	.long	23                      ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	0                       ## Bucket 0
	.long	1                       ## Bucket 1
	.long	7                       ## Bucket 2
	.long	9                       ## Bucket 3
	.long	10                      ## Bucket 4
	.long	13                      ## Bucket 5
	.long	15                      ## Bucket 6
	.long	16                      ## Bucket 7
	.long	18                      ## Bucket 8
	.long	19                      ## Bucket 9
	.long	20                      ## Bucket 10
	.long	2090087087              ## Hash in Bucket 0
	.long	1018014229              ## Hash in Bucket 1
	.long	1066064330              ## Hash in Bucket 1
	.long	1370510241              ## Hash in Bucket 1
	.long	-2004849355             ## Hash in Bucket 1
	.long	-1867655056             ## Hash in Bucket 1
	.long	-529230144              ## Hash in Bucket 1
	.long	1777782019              ## Hash in Bucket 2
	.long	-1067484673             ## Hash in Bucket 2
	.long	1846692543              ## Hash in Bucket 3
	.long	326627679               ## Hash in Bucket 4
	.long	1926731063              ## Hash in Bucket 4
	.long	-1735512922             ## Hash in Bucket 4
	.long	818398850               ## Hash in Bucket 5
	.long	-311502190              ## Hash in Bucket 5
	.long	-2005979919             ## Hash in Bucket 6
	.long	777759132               ## Hash in Bucket 7
	.long	2090499946              ## Hash in Bucket 7
	.long	-1686033257             ## Hash in Bucket 8
	.long	-1734890812             ## Hash in Bucket 9
	.long	199252646               ## Hash in Bucket 10
	.long	1172667473              ## Hash in Bucket 10
	.long	-1338544102             ## Hash in Bucket 10
	.long	LNames6-Lnames_begin    ## Offset in Bucket 0
	.long	LNames12-Lnames_begin   ## Offset in Bucket 1
	.long	LNames4-Lnames_begin    ## Offset in Bucket 1
	.long	LNames22-Lnames_begin   ## Offset in Bucket 1
	.long	LNames11-Lnames_begin   ## Offset in Bucket 1
	.long	LNames7-Lnames_begin    ## Offset in Bucket 1
	.long	LNames19-Lnames_begin   ## Offset in Bucket 1
	.long	LNames21-Lnames_begin   ## Offset in Bucket 2
	.long	LNames20-Lnames_begin   ## Offset in Bucket 2
	.long	LNames17-Lnames_begin   ## Offset in Bucket 3
	.long	LNames18-Lnames_begin   ## Offset in Bucket 4
	.long	LNames13-Lnames_begin   ## Offset in Bucket 4
	.long	LNames2-Lnames_begin    ## Offset in Bucket 4
	.long	LNames0-Lnames_begin    ## Offset in Bucket 5
	.long	LNames9-Lnames_begin    ## Offset in Bucket 5
	.long	LNames8-Lnames_begin    ## Offset in Bucket 6
	.long	LNames16-Lnames_begin   ## Offset in Bucket 7
	.long	LNames3-Lnames_begin    ## Offset in Bucket 7
	.long	LNames14-Lnames_begin   ## Offset in Bucket 8
	.long	LNames5-Lnames_begin    ## Offset in Bucket 9
	.long	LNames1-Lnames_begin    ## Offset in Bucket 10
	.long	LNames10-Lnames_begin   ## Offset in Bucket 10
	.long	LNames15-Lnames_begin   ## Offset in Bucket 10
LNames6:
	.long	127                     ## arg0
	.long	1                       ## Num DIEs
	.long	131
	.long	0
LNames12:
	.long	1047                    ## exec_pipe_command
	.long	1                       ## Num DIEs
	.long	3270
	.long	0
LNames4:
	.long	745                     ## dump_argv
	.long	1                       ## Num DIEs
	.long	2295
	.long	0
LNames22:
	.long	968                     ## spawn_proc
	.long	1                       ## Num DIEs
	.long	2751
	.long	0
LNames11:
	.long	999                     ## err_syserr
	.long	1                       ## Num DIEs
	.long	2860
	.long	0
LNames7:
	.long	863                     ## dump_pipeline
	.long	1                       ## Num DIEs
	.long	2346
	.long	0
LNames19:
	.long	85                      ## foreground
	.long	1                       ## Num DIEs
	.long	76
	.long	0
LNames21:
	.long	845                     ## err_setarg0
	.long	1                       ## Num DIEs
	.long	2407
	.long	0
LNames20:
	.long	72                      ## isSignal
	.long	1                       ## Num DIEs
	.long	47
	.long	0
LNames17:
	.long	771                     ## exec_arguments
	.long	1                       ## Num DIEs
	.long	2265
	.long	0
LNames18:
	.long	877                     ## exec_pipeline
	.long	1                       ## Num DIEs
	.long	2385
	.long	0
LNames13:
	.long	906                     ## corpse_collector
	.long	1                       ## Num DIEs
	.long	2431
	.long	0
LNames2:
	.long	1010                    ## err_sysexit
	.long	1                       ## Num DIEs
	.long	2933
	.long	0
LNames0:
	.long	832                     ## StartsWith
	.long	3                       ## Num DIEs
	.long	2610
	.long	2634
	.long	2664
	.long	0
LNames9:
	.long	810                     ## RemoveSpaces
	.long	1                       ## Num DIEs
	.long	2588
	.long	0
LNames8:
	.long	137                     ## file_exist
	.long	1                       ## Num DIEs
	.long	2185
	.long	0
LNames16:
	.long	720                     ## Janitor
	.long	3                       ## Num DIEs
	.long	2216
	.long	2489
	.long	2539
	.long	0
LNames3:
	.long	983                     ## main
	.long	1                       ## Num DIEs
	.long	1486
	.long	0
LNames14:
	.long	937                     ## fork_pipes
	.long	1                       ## Num DIEs
	.long	2694
	.long	0
LNames5:
	.long	1035                    ## err_syswarn
	.long	1                       ## Num DIEs
	.long	3064
	.long	0
LNames1:
	.long	988                     ## sighandler
	.long	1                       ## Num DIEs
	.long	2775
	.long	0
LNames10:
	.long	1072                    ## exec_nth_command
	.long	1                       ## Num DIEs
	.long	3167
	.long	0
LNames15:
	.long	1022                    ## err_vsyswarn
	.long	1                       ## Num DIEs
	.long	2991
	.long	0
	.section	__DWARF,__apple_objc,regular,debug
Lobjc_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.section	__DWARF,__apple_namespac,regular,debug
Lnamespac_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.section	__DWARF,__apple_types,regular,debug
Ltypes_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	26                      ## Header Bucket Count
	.long	52                      ## Header Hash Count
	.long	20                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	3                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.short	3                       ## DW_ATOM_die_tag
	.short	5                       ## DW_FORM_data2
	.short	4                       ## DW_ATOM_type_flags
	.short	11                      ## DW_FORM_data1
	.long	-1                      ## Bucket 0
	.long	0                       ## Bucket 1
	.long	2                       ## Bucket 2
	.long	4                       ## Bucket 3
	.long	7                       ## Bucket 4
	.long	-1                      ## Bucket 5
	.long	8                       ## Bucket 6
	.long	9                       ## Bucket 7
	.long	11                      ## Bucket 8
	.long	14                      ## Bucket 9
	.long	16                      ## Bucket 10
	.long	18                      ## Bucket 11
	.long	19                      ## Bucket 12
	.long	20                      ## Bucket 13
	.long	21                      ## Bucket 14
	.long	22                      ## Bucket 15
	.long	26                      ## Bucket 16
	.long	-1                      ## Bucket 17
	.long	29                      ## Bucket 18
	.long	30                      ## Bucket 19
	.long	33                      ## Bucket 20
	.long	38                      ## Bucket 21
	.long	-1                      ## Bucket 22
	.long	42                      ## Bucket 23
	.long	47                      ## Bucket 24
	.long	48                      ## Bucket 25
	.long	-1304652851             ## Hash in Bucket 1
	.long	-503405833              ## Hash in Bucket 1
	.long	255285318               ## Hash in Bucket 2
	.long	-627816040              ## Hash in Bucket 2
	.long	1950644907              ## Hash in Bucket 3
	.long	2089466707              ## Hash in Bucket 3
	.long	2090736001              ## Hash in Bucket 3
	.long	-2056653344             ## Hash in Bucket 4
	.long	1742219576              ## Hash in Bucket 6
	.long	238190973               ## Hash in Bucket 7
	.long	679906663               ## Hash in Bucket 7
	.long	276790522               ## Hash in Bucket 8
	.long	-1880351968             ## Hash in Bucket 8
	.long	-1267332080             ## Hash in Bucket 8
	.long	2090147939              ## Hash in Bucket 9
	.long	-1503406983             ## Hash in Bucket 9
	.long	1771224946              ## Hash in Bucket 10
	.long	-1718803696             ## Hash in Bucket 10
	.long	269569363               ## Hash in Bucket 11
	.long	260187628               ## Hash in Bucket 12
	.long	-243996567              ## Hash in Bucket 13
	.long	878862258               ## Hash in Bucket 14
	.long	256505719               ## Hash in Bucket 15
	.long	270860917               ## Hash in Bucket 15
	.long	466014187               ## Hash in Bucket 15
	.long	-282664779              ## Hash in Bucket 15
	.long	-748447420              ## Hash in Bucket 16
	.long	-586885526              ## Hash in Bucket 16
	.long	-136368420              ## Hash in Bucket 16
	.long	1980690028              ## Hash in Bucket 18
	.long	688950281               ## Hash in Bucket 19
	.long	-1308701839             ## Hash in Bucket 19
	.long	-143589579              ## Hash in Bucket 19
	.long	193495088               ## Hash in Bucket 20
	.long	450694836               ## Hash in Bucket 20
	.long	1733175958              ## Hash in Bucket 20
	.long	1950534918              ## Hash in Bucket 20
	.long	-152971314              ## Hash in Bucket 20
	.long	339549335               ## Hash in Bucket 21
	.long	580916487               ## Hash in Bucket 21
	.long	2096540779              ## Hash in Bucket 21
	.long	-2056763333             ## Hash in Bucket 21
	.long	505346631               ## Hash in Bucket 23
	.long	1750082071              ## Hash in Bucket 23
	.long	-511152225              ## Hash in Bucket 23
	.long	-156653223              ## Hash in Bucket 23
	.long	-142298025              ## Hash in Bucket 23
	.long	-2015837874             ## Hash in Bucket 24
	.long	466678419               ## Hash in Bucket 25
	.long	-2056830851             ## Hash in Bucket 25
	.long	-80380739               ## Hash in Bucket 25
	.long	-69895251               ## Hash in Bucket 25
	.long	Ltypes23-Ltypes_begin   ## Offset in Bucket 1
	.long	Ltypes9-Ltypes_begin    ## Offset in Bucket 1
	.long	Ltypes14-Ltypes_begin   ## Offset in Bucket 2
	.long	Ltypes48-Ltypes_begin   ## Offset in Bucket 2
	.long	Ltypes2-Ltypes_begin    ## Offset in Bucket 3
	.long	Ltypes33-Ltypes_begin   ## Offset in Bucket 3
	.long	Ltypes51-Ltypes_begin   ## Offset in Bucket 3
	.long	Ltypes12-Ltypes_begin   ## Offset in Bucket 4
	.long	Ltypes7-Ltypes_begin    ## Offset in Bucket 6
	.long	Ltypes18-Ltypes_begin   ## Offset in Bucket 7
	.long	Ltypes38-Ltypes_begin   ## Offset in Bucket 7
	.long	Ltypes34-Ltypes_begin   ## Offset in Bucket 8
	.long	Ltypes13-Ltypes_begin   ## Offset in Bucket 8
	.long	Ltypes43-Ltypes_begin   ## Offset in Bucket 8
	.long	Ltypes35-Ltypes_begin   ## Offset in Bucket 9
	.long	Ltypes49-Ltypes_begin   ## Offset in Bucket 9
	.long	Ltypes26-Ltypes_begin   ## Offset in Bucket 10
	.long	Ltypes46-Ltypes_begin   ## Offset in Bucket 10
	.long	Ltypes16-Ltypes_begin   ## Offset in Bucket 11
	.long	Ltypes22-Ltypes_begin   ## Offset in Bucket 12
	.long	Ltypes1-Ltypes_begin    ## Offset in Bucket 13
	.long	Ltypes45-Ltypes_begin   ## Offset in Bucket 14
	.long	Ltypes31-Ltypes_begin   ## Offset in Bucket 15
	.long	Ltypes29-Ltypes_begin   ## Offset in Bucket 15
	.long	Ltypes15-Ltypes_begin   ## Offset in Bucket 15
	.long	Ltypes30-Ltypes_begin   ## Offset in Bucket 15
	.long	Ltypes36-Ltypes_begin   ## Offset in Bucket 16
	.long	Ltypes41-Ltypes_begin   ## Offset in Bucket 16
	.long	Ltypes10-Ltypes_begin   ## Offset in Bucket 16
	.long	Ltypes24-Ltypes_begin   ## Offset in Bucket 18
	.long	Ltypes40-Ltypes_begin   ## Offset in Bucket 19
	.long	Ltypes44-Ltypes_begin   ## Offset in Bucket 19
	.long	Ltypes47-Ltypes_begin   ## Offset in Bucket 19
	.long	Ltypes25-Ltypes_begin   ## Offset in Bucket 20
	.long	Ltypes28-Ltypes_begin   ## Offset in Bucket 20
	.long	Ltypes5-Ltypes_begin    ## Offset in Bucket 20
	.long	Ltypes37-Ltypes_begin   ## Offset in Bucket 20
	.long	Ltypes3-Ltypes_begin    ## Offset in Bucket 20
	.long	Ltypes32-Ltypes_begin   ## Offset in Bucket 21
	.long	Ltypes39-Ltypes_begin   ## Offset in Bucket 21
	.long	Ltypes21-Ltypes_begin   ## Offset in Bucket 21
	.long	Ltypes50-Ltypes_begin   ## Offset in Bucket 21
	.long	Ltypes0-Ltypes_begin    ## Offset in Bucket 23
	.long	Ltypes17-Ltypes_begin   ## Offset in Bucket 23
	.long	Ltypes20-Ltypes_begin   ## Offset in Bucket 23
	.long	Ltypes8-Ltypes_begin    ## Offset in Bucket 23
	.long	Ltypes6-Ltypes_begin    ## Offset in Bucket 23
	.long	Ltypes4-Ltypes_begin    ## Offset in Bucket 24
	.long	Ltypes27-Ltypes_begin   ## Offset in Bucket 25
	.long	Ltypes19-Ltypes_begin   ## Offset in Bucket 25
	.long	Ltypes11-Ltypes_begin   ## Offset in Bucket 25
	.long	Ltypes42-Ltypes_begin   ## Offset in Bucket 25
Ltypes23:
	.long	368                     ## unsigned int
	.long	1                       ## Num DIEs
	.long	668
	.short	36
	.byte	0
	.long	0
Ltypes9:
	.long	1650                    ## timeval
	.long	1                       ## Num DIEs
	.long	3937
	.short	19
	.byte	0
	.long	0
Ltypes14:
	.long	1220                    ## sigaction
	.long	1                       ## Num DIEs
	.long	3398
	.short	19
	.byte	0
	.long	0
Ltypes48:
	.long	1230                    ## __sigaction_u
	.long	1                       ## Num DIEs
	.long	3453
	.short	23
	.byte	0
	.long	0
Ltypes2:
	.long	574                     ## __int64_t
	.long	1                       ## Num DIEs
	.long	748
	.short	22
	.byte	0
	.long	0
Ltypes33:
	.long	1908                    ## Pipe
	.long	1                       ## Num DIEs
	.long	4140
	.short	22
	.byte	0
	.long	0
Ltypes51:
	.long	164                     ## stat
	.long	1                       ## Num DIEs
	.long	215
	.short	19
	.byte	0
	.long	0
Ltypes12:
	.long	295                     ## __uint64_t
	.long	1                       ## Num DIEs
	.long	617
	.short	22
	.byte	0
	.long	0
Ltypes7:
	.long	617                     ## __darwin_blkcnt_t
	.long	1                       ## Num DIEs
	.long	777
	.short	22
	.byte	0
	.long	0
Ltypes18:
	.long	205                     ## mode_t
	.long	1                       ## Num DIEs
	.long	555
	.short	22
	.byte	0
	.long	0
Ltypes38:
	.long	1416                    ## sigset_t
	.long	1                       ## Num DIEs
	.long	3739
	.short	22
	.byte	0
	.long	0
Ltypes34:
	.long	336                     ## uid_t
	.long	1                       ## Num DIEs
	.long	635
	.short	22
	.byte	0
	.long	0
Ltypes13:
	.long	449                     ## long int
	.long	1                       ## Num DIEs
	.long	719
	.short	36
	.byte	0
	.long	0
Ltypes43:
	.long	584                     ## long long int
	.long	1                       ## Num DIEs
	.long	759
	.short	36
	.byte	0
	.long	0
Ltypes35:
	.long	132                     ## char
	.long	1                       ## Num DIEs
	.long	162
	.short	36
	.byte	0
	.long	0
Ltypes49:
	.long	1790                    ## __darwin_va_list
	.long	1                       ## Num DIEs
	.long	4036
	.short	22
	.byte	0
	.long	0
Ltypes26:
	.long	1272                    ## __siginfo
	.long	1                       ## Num DIEs
	.long	3534
	.short	19
	.byte	0
	.long	0
Ltypes46:
	.long	1825                    ## __va_list_tag
	.long	1                       ## Num DIEs
	.long	4070
	.short	19
	.byte	0
	.long	0
Ltypes16:
	.long	553                     ## off_t
	.long	1                       ## Num DIEs
	.long	726
	.short	22
	.byte	0
	.long	0
Ltypes22:
	.long	388                     ## gid_t
	.long	1                       ## Num DIEs
	.long	675
	.short	22
	.byte	0
	.long	0
Ltypes1:
	.long	433                     ## __darwin_time_t
	.long	1                       ## Num DIEs
	.long	708
	.short	22
	.byte	0
	.long	0
Ltypes45:
	.long	239                     ## unsigned short
	.long	1                       ## Num DIEs
	.long	588
	.short	36
	.byte	0
	.long	0
Ltypes31:
	.long	176                     ## dev_t
	.long	1                       ## Num DIEs
	.long	533
	.short	22
	.byte	0
	.long	0
Ltypes29:
	.long	96                      ## pid_t
	.long	1                       ## Num DIEs
	.long	98
	.short	22
	.byte	0
	.long	0
Ltypes15:
	.long	1349                    ## sigval
	.long	1                       ## Num DIEs
	.long	3683
	.short	23
	.byte	0
	.long	0
Ltypes30:
	.long	1510                    ## __darwin_size_t
	.long	1                       ## Num DIEs
	.long	3772
	.short	22
	.byte	0
	.long	0
Ltypes36:
	.long	954                     ## command
	.long	1                       ## Num DIEs
	.long	1382
	.short	19
	.byte	0
	.long	0
Ltypes41:
	.long	278                     ## __darwin_ino64_t
	.long	1                       ## Num DIEs
	.long	606
	.short	22
	.byte	0
	.long	0
Ltypes10:
	.long	342                     ## __darwin_uid_t
	.long	1                       ## Num DIEs
	.long	646
	.short	22
	.byte	0
	.long	0
Ltypes24:
	.long	646                     ## blksize_t
	.long	1                       ## Num DIEs
	.long	788
	.short	22
	.byte	0
	.long	0
Ltypes40:
	.long	1425                    ## __darwin_sigset_t
	.long	1                       ## Num DIEs
	.long	3750
	.short	22
	.byte	0
	.long	0
Ltypes44:
	.long	1673                    ## __darwin_suseconds_t
	.long	1                       ## Num DIEs
	.long	3974
	.short	22
	.byte	0
	.long	0
Ltypes47:
	.long	559                     ## __darwin_off_t
	.long	1                       ## Num DIEs
	.long	737
	.short	22
	.byte	0
	.long	0
Ltypes25:
	.long	81                      ## int
	.long	1                       ## Num DIEs
	.long	69
	.short	36
	.byte	0
	.long	0
Ltypes28:
	.long	263                     ## nlink_t
	.long	1                       ## Num DIEs
	.long	595
	.short	22
	.byte	0
	.long	0
Ltypes5:
	.long	608                     ## blkcnt_t
	.long	1                       ## Num DIEs
	.long	766
	.short	22
	.byte	0
	.long	0
Ltypes37:
	.long	117                     ## __int32_t
	.long	1                       ## Num DIEs
	.long	120
	.short	22
	.byte	0
	.long	0
Ltypes3:
	.long	394                     ## __darwin_gid_t
	.long	1                       ## Num DIEs
	.long	686
	.short	22
	.byte	0
	.long	0
Ltypes32:
	.long	1538                    ## passwd
	.long	1                       ## Num DIEs
	.long	3788
	.short	19
	.byte	0
	.long	0
Ltypes39:
	.long	1756                    ## siginfo_t
	.long	1                       ## Num DIEs
	.long	4014
	.short	22
	.byte	0
	.long	0
Ltypes21:
	.long	1807                    ## __builtin_va_list
	.long	1                       ## Num DIEs
	.long	4047
	.short	22
	.byte	0
	.long	0
Ltypes50:
	.long	357                     ## __uint32_t
	.long	1                       ## Num DIEs
	.long	657
	.short	22
	.byte	0
	.long	0
Ltypes0:
	.long	426                     ## time_t
	.long	1                       ## Num DIEs
	.long	697
	.short	22
	.byte	0
	.long	0
Ltypes17:
	.long	1782                    ## va_list
	.long	1                       ## Num DIEs
	.long	4025
	.short	22
	.byte	0
	.long	0
Ltypes20:
	.long	212                     ## __darwin_mode_t
	.long	1                       ## Num DIEs
	.long	566
	.short	22
	.byte	0
	.long	0
Ltypes8:
	.long	182                     ## __darwin_dev_t
	.long	1                       ## Num DIEs
	.long	544
	.short	22
	.byte	0
	.long	0
Ltypes6:
	.long	102                     ## __darwin_pid_t
	.long	1                       ## Num DIEs
	.long	109
	.short	22
	.byte	0
	.long	0
Ltypes4:
	.long	656                     ## __darwin_blksize_t
	.long	1                       ## Num DIEs
	.long	799
	.short	22
	.byte	0
	.long	0
Ltypes27:
	.long	1503                    ## size_t
	.long	1                       ## Num DIEs
	.long	3761
	.short	22
	.byte	0
	.long	0
Ltypes19:
	.long	228                     ## __uint16_t
	.long	1                       ## Num DIEs
	.long	577
	.short	22
	.byte	0
	.long	0
Ltypes11:
	.long	1390                    ## long unsigned int
	.long	1                       ## Num DIEs
	.long	3732
	.short	36
	.byte	0
	.long	0
Ltypes42:
	.long	306                     ## long long unsigned int
	.long	1                       ## Num DIEs
	.long	628
	.short	36
	.byte	0
	.long	0
	.section	__DWARF,__apple_exttypes,regular,debug
Lexttypes_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	7                       ## DW_ATOM_ext_types
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0

.subsections_via_symbols
	.section	__DWARF,__debug_line,regular,debug
Lsection_line:
Lline_table_start0:
