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
	subq	$2552, %rsp             ## imm = 0x9F8
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
	leaq	-192(%rbp), %r15
	.loc	1 321 25                ## c_posix.c:321:25
Ltmp44:
	leaq	L_.str.28(%rip), %r13
Ltmp45:
	.loc	1 117 9                 ## c_posix.c:117:9
	leaq	L_.str.44(%rip), %r12
	movl	$0, -2516(%rbp)         ## 4-byte Folded Spill
	jmp	LBB0_11
LBB0_116:                               ##   in Loop: Header=BB0_11 Depth=1
	leaq	L_.str.44(%rip), %r12
Ltmp46:
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
	.loc	1 464 9                 ## c_posix.c:464:9
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
                                        ##     Child Loop BB0_102 Depth 2
                                        ##     Child Loop BB0_109 Depth 2
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
	##DEBUG_VALUE: a <- 1
	.loc	1 308 29                ## c_posix.c:308:29
	movl	$-1, %edi
	movl	$1, %edx
	movq	%r15, %rsi
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
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
	leaq	-1248(%rbp), %r14
	movq	%r14, %rdi
	callq	___bzero
	.loc	1 465 38                ## c_posix.c:465:38
Ltmp58:
	movq	___stdinp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdx
	.loc	1 465 14 is_stmt 0      ## c_posix.c:465:14
	movl	$1024, %esi             ## imm = 0x400
	movq	%r14, %rdi
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
	##DEBUG_VALUE: a <- 1
	.loc	1 308 29                ## c_posix.c:308:29
	movl	$-1, %edi
	movl	$1, %edx
Ltmp64:
	.loc	1 308 29 is_stmt 0      ## c_posix.c:308:29
	movq	%r15, %rsi
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
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
	.loc	1 501 28                ## c_posix.c:501:28
Ltmp89:
	leaq	L_.str(%rip), %r13
	jne	LBB0_35
Ltmp90:
## BB#29:                               ##   in Loop: Header=BB0_11 Depth=1
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
Ltmp91:
	callq	_strchr
Ltmp92:
	.loc	1 489 17 is_stmt 0      ## c_posix.c:489:17
	testq	%rax, %rax
	je	LBB0_30
## BB#32:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp93:
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
Ltmp94:
	movq	%r13, %rsi
	callq	_strtok
	xorl	%edi, %edi
	.loc	1 502 28                ## c_posix.c:502:28
	movq	%r13, %rsi
	callq	_strtok
Ltmp95:
	##DEBUG_VALUE: main:tokenstr <- %RAX
	.loc	1 504 21                ## c_posix.c:504:21
	movq	%rax, %rdi
	callq	_chdir
Ltmp96:
	movl	$1, %r14d
Ltmp97:
	.loc	1 504 21 is_stmt 0      ## c_posix.c:504:21
	cmpl	$-1, %eax
	jne	LBB0_35
## BB#33:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp98:
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
Ltmp99:
	jmp	LBB0_34
Ltmp100:
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
Ltmp101:
	callq	_getpwuid
Ltmp102:
	##DEBUG_VALUE: main:pw <- %RAX
	.loc	1 492 31 is_stmt 1      ## c_posix.c:492:31
	movq	48(%rax), %rdi
Ltmp103:
	##DEBUG_VALUE: main:homedir <- %RDI
	.loc	1 494 21                ## c_posix.c:494:21
	callq	_chdir
Ltmp104:
	movl	$1, %r14d
Ltmp105:
	.loc	1 494 21 is_stmt 0      ## c_posix.c:494:21
	cmpl	$-1, %eax
	je	LBB0_31
Ltmp106:
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
Ltmp107:
	leaq	L_.str.16(%rip), %rsi
	callq	_strncmp
Ltmp108:
	.loc	1 516 13                ## c_posix.c:516:13
	testl	%eax, %eax
	je	LBB0_36
## BB#64:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp109:
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
	xorl	%r12d, %r12d
	.loc	1 568 13                ## c_posix.c:568:13
	testl	%r14d, %r14d
	movl	$4, %eax
	movl	$1, %edx
	jne	LBB0_115
Ltmp110:
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
Ltmp111:
	##DEBUG_VALUE: main:isBackground <- 1
	movzbl	-1251(%rbp,%rax), %ecx
Ltmp112:
	.loc	1 581 21 is_stmt 0      ## c_posix.c:581:21
	cmovel	%edx, %r12d
	.loc	1 581 25                ## c_posix.c:581:25
Ltmp113:
	cmpl	$38, %ecx
	movzbl	-1250(%rbp,%rax), %ecx
Ltmp114:
	.loc	1 581 21                ## c_posix.c:581:21
	cmovel	%edx, %r12d
	.loc	1 581 25                ## c_posix.c:581:25
Ltmp115:
	cmpl	$38, %ecx
	movzbl	-1249(%rbp,%rax), %ecx
Ltmp116:
	.loc	1 581 21                ## c_posix.c:581:21
	cmovel	%edx, %r12d
	.loc	1 581 25                ## c_posix.c:581:25
Ltmp117:
	cmpl	$38, %ecx
	movzbl	-1248(%rbp,%rax), %ecx
Ltmp118:
	.loc	1 581 21                ## c_posix.c:581:21
	cmovel	%edx, %r12d
	.loc	1 581 25                ## c_posix.c:581:25
Ltmp119:
	cmpl	$38, %ecx
Ltmp120:
	.loc	1 581 21                ## c_posix.c:581:21
	cmovel	%edx, %r12d
Ltmp121:
	.loc	1 579 13 is_stmt 1      ## c_posix.c:579:13
	addq	$5, %rax
	cmpq	$84, %rax
	jne	LBB0_65
Ltmp122:
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
	cmpl	$1, %r12d
	jne	LBB0_70
Ltmp123:
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
Ltmp124:
	.loc	1 590 21                ## c_posix.c:590:21
	callq	_pipe
Ltmp125:
	.loc	1 590 21 is_stmt 0      ## c_posix.c:590:21
	cmpl	$-1, %eax
	je	LBB0_68
LBB0_69:                                ##   in Loop: Header=BB0_11 Depth=1
Ltmp126:
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
	.loc	1 595 28 is_stmt 1      ## c_posix.c:595:28
	callq	_fork
	movl	%eax, -2516(%rbp)       ## 4-byte Spill
Ltmp127:
	##DEBUG_VALUE: main:pid_temp <- [%RBP+-2516]
	jmp	LBB0_74
Ltmp128:
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
	testl	%r12d, %r12d
	jne	LBB0_74
Ltmp129:
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
Ltmp130:
	.loc	1 599 17                ## c_posix.c:599:17
	callq	_gettimeofday
	.loc	1 601 21                ## c_posix.c:601:21
	cmpl	$1, _isSignal(%rip)
	jne	LBB0_73
## BB#72:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp131:
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
Ltmp132:
	##DEBUG_VALUE: main:my_sig <- undef
	movl	$1, %edi
Ltmp133:
	xorl	%edx, %edx
	leaq	-2444(%rbp), %rsi
	.loc	1 606 21                ## c_posix.c:606:21
	callq	_sigprocmask
Ltmp134:
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
Ltmp135:
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
Ltmp136:
	movq	%rax, _arg0(%rip)
Ltmp137:
	##DEBUG_VALUE: main:i <- 1
	.loc	1 615 17                ## c_posix.c:615:17
	movq	%rbx, %rdi
Ltmp138:
	movq	%r13, %rsi
	callq	_strtok
Ltmp139:
	##DEBUG_VALUE: main:p <- %RAX
	.loc	1 617 22                ## c_posix.c:617:22
	movq	$0, -224(%rbp)
	movl	$1, %r14d
	.loc	1 618 22                ## c_posix.c:618:22
	testq	%rax, %rax
	movl	$1, %ebx
	je	LBB0_77
Ltmp140:
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
Ltmp141:
	.loc	1 618 13                ## c_posix.c:618:13
	incq	%rbx
	xorl	%edi, %edi
Ltmp142:
	.loc	1 621 21                ## c_posix.c:621:21
	movq	%r13, %rsi
	callq	_strtok
Ltmp143:
	##DEBUG_VALUE: main:p <- %RAX
	.loc	1 618 13                ## c_posix.c:618:13
	testq	%rax, %rax
	jne	LBB0_75
Ltmp144:
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
Ltmp145:
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
Ltmp146:
	leaq	L_.str.43(%rip), %rdi
Ltmp147:
	leaq	L_.str.37(%rip), %rsi
	movl	%ebx, %edx
	callq	_printf
Ltmp148:
	##DEBUG_VALUE: i <- 0
	.loc	1 116 5                 ## c_posix.c:116:5
	testl	%ebx, %ebx
	leaq	-224(%rbp), %rbx
	.loc	1 117 9                 ## c_posix.c:117:9
Ltmp149:
	leaq	L_.str.44(%rip), %r13
	jle	LBB0_79
	.align	4, 0x90
LBB0_78:                                ## %.lr.ph.i.i
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
Ltmp150:
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
	.loc	1 117 26 is_stmt 0      ## c_posix.c:117:26
	movq	(%rbx), %rsi
	.loc	1 117 34                ## c_posix.c:117:34
	testq	%rsi, %rsi
	.loc	1 117 25                ## c_posix.c:117:25
	leaq	L_.str.45(%rip), %rax
	cmoveq	%rax, %rsi
	xorl	%eax, %eax
	.loc	1 117 9                 ## c_posix.c:117:9
	movq	%r13, %rdi
Ltmp151:
	callq	_printf
Ltmp152:
	.loc	1 116 5 is_stmt 1       ## c_posix.c:116:5
	addq	$8, %rbx
	decl	%r14d
	jne	LBB0_78
Ltmp153:
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
Ltmp154:
	callq	_putchar
	.loc	1 119 12                ## c_posix.c:119:12
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rdi
	.loc	1 119 5 is_stmt 0       ## c_posix.c:119:5
	callq	_fflush
	movq	-2512(%rbp), %rbx       ## 8-byte Reload
Ltmp155:
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
Ltmp156:
	##DEBUG_VALUE: exec_arguments:argn <- 0
	##DEBUG_VALUE: exec_arguments:cmdn <- 1
	.loc	1 149 18 is_stmt 1      ## c_posix.c:149:18
	movq	%rax, -2504(%rbp)       ## 8-byte Spill
	movq	%rax, (%r14)
Ltmp157:
	##DEBUG_VALUE: i <- 1
	movl	$1, -2488(%rbp)         ## 4-byte Folded Spill
	xorl	%r14d, %r14d
	.loc	1 151 23                ## c_posix.c:151:23
Ltmp158:
	cmpl	$1, %ebx
	movl	$1, %ebx
	jle	LBB0_80
	.align	4, 0x90
LBB0_82:                                ## %.lr.ph.i.9
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
Ltmp159:
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
	movq	-224(%rbp,%rbx,8), %r13
Ltmp160:
	##DEBUG_VALUE: arg <- %R13
	.loc	1 155 13                ## c_posix.c:155:13
	movq	%r13, %rdi
Ltmp161:
	leaq	L_.str.21(%rip), %rsi
	callq	_strcmp
Ltmp162:
	.loc	1 155 13 is_stmt 0      ## c_posix.c:155:13
	testl	%eax, %eax
	je	LBB0_83
Ltmp163:
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
	##DEBUG_VALUE: exec_arguments:argn <- %R14D
	##DEBUG_VALUE: i <- 1
	##DEBUG_VALUE: arg <- %R13
	.loc	1 163 9 is_stmt 1       ## c_posix.c:163:9
	movslq	%r14d, %rcx
	.loc	1 163 18 is_stmt 0      ## c_posix.c:163:18
	incl	%r14d
Ltmp164:
	movq	-2504(%rbp), %rax       ## 8-byte Reload
	.loc	1 163 22                ## c_posix.c:163:22
	movq	%r13, (%rax,%rcx,8)
	.loc	1 164 13 is_stmt 1      ## c_posix.c:164:13
	testq	%r13, %r13
	jne	LBB0_89
	jmp	LBB0_88
Ltmp165:
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
	cmpq	$1, %rbx
	movq	-2504(%rbp), %rax       ## 8-byte Reload
	je	LBB0_122
Ltmp166:
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
	movslq	%r14d, %rcx
	.loc	1 159 32 is_stmt 0      ## c_posix.c:159:32
	cmpq	$0, -8(%rax,%rcx,8)
Ltmp167:
	.loc	1 159 17                ## c_posix.c:159:17
	je	LBB0_86
Ltmp168:
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
	incl	%r14d
	.loc	1 163 22 is_stmt 0      ## c_posix.c:163:22
	movq	$0, (%rax,%rcx,8)
Ltmp169:
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
	movslq	%r14d, %rcx
	leaq	(%rax,%rcx,8), %rsi
Ltmp170:
	##DEBUG_VALUE: exec_arguments:cmdn <- [%RBP+-2488]
	movl	-2488(%rbp), %edx       ## 4-byte Reload
Ltmp171:
	##DEBUG_VALUE: exec_arguments:cmdn <- %EDX
	.loc	1 165 13 is_stmt 0      ## c_posix.c:165:13
	movslq	%edx, %rcx
	.loc	1 165 22                ## c_posix.c:165:22
	incl	%edx
Ltmp172:
	movl	%edx, -2488(%rbp)       ## 4-byte Spill
	.loc	1 165 26                ## c_posix.c:165:26
	movq	-2496(%rbp), %rdx       ## 8-byte Reload
	movq	%rsi, (%rdx,%rcx,8)
Ltmp173:
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
	incq	%rbx
	.loc	1 151 23 is_stmt 0      ## c_posix.c:151:23
Ltmp174:
	cmpq	-2512(%rbp), %rbx       ## 8-byte Folded Reload
	jl	LBB0_82
Ltmp175:
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
	movslq	%r14d, %rcx
	.loc	1 167 24 is_stmt 0      ## c_posix.c:167:24
	cmpq	$0, -8(%rax,%rcx,8)
	je	LBB0_81
Ltmp176:
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
Ltmp177:
	leaq	L_str.57(%rip), %rdi
Ltmp178:
	callq	_puts
Ltmp179:
	##DEBUG_VALUE: i <- 0
	.loc	1 126 5                 ## c_posix.c:126:5
	cmpl	$0, -2488(%rbp)         ## 4-byte Folded Reload
	movl	$0, %r13d
Ltmp180:
	.loc	1 117 9                 ## c_posix.c:117:9
	leaq	L_.str.44(%rip), %r14
	jle	LBB0_95
Ltmp181:
	.align	4, 0x90
LBB0_91:                                ## %.lr.ph5.i.i
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Loop Header: Depth=2
                                        ##       Child Loop BB0_93 Depth 3
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
Ltmp182:
	leaq	L_.str.50(%rip), %rdi
Ltmp183:
	movl	%r13d, %esi
	callq	_printf
	.loc	1 129 23                ## c_posix.c:129:23
	movq	-2496(%rbp), %rax       ## 8-byte Reload
	movq	(%rax,%r13,8), %rbx
Ltmp184:
	##DEBUG_VALUE: args <- %RBX
	.loc	1 130 16                ## c_posix.c:130:16
	movq	(%rbx), %rsi
	.loc	1 130 22 is_stmt 0      ## c_posix.c:130:22
	testq	%rsi, %rsi
	je	LBB0_94
Ltmp185:
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
	.loc	1 131 34 is_stmt 1      ## c_posix.c:131:34
	addq	$8, %rbx
Ltmp186:
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
	movq	%r14, %rdi
Ltmp187:
	callq	_printf
	.loc	1 130 16 is_stmt 1      ## c_posix.c:130:16
	movq	(%rbx), %rsi
	.loc	1 130 9 is_stmt 0       ## c_posix.c:130:9
	addq	$8, %rbx
	testq	%rsi, %rsi
	jne	LBB0_93
Ltmp188:
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
Ltmp189:
	.loc	1 132 9                 ## c_posix.c:132:9
	callq	_putchar
Ltmp190:
	.loc	1 126 5                 ## c_posix.c:126:5
	incq	%r13
	cmpl	-2488(%rbp), %r13d      ## 4-byte Folded Reload
	jne	LBB0_91
Ltmp191:
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
	leaq	L_str.58(%rip), %rdi
Ltmp192:
	callq	_puts
Ltmp193:
	.loc	1 119 12                ## c_posix.c:119:12
	movq	___stdoutp@GOTPCREL(%rip), %rax
Ltmp194:
	.loc	1 135 12                ## c_posix.c:135:12
	movq	(%rax), %rdi
	.loc	1 135 5 is_stmt 0       ## c_posix.c:135:5
	callq	_fflush
Ltmp195:
	.loc	1 88 5 is_stmt 1        ## c_posix.c:88:5
	cmpl	$0, -2488(%rbp)         ## 4-byte Folded Reload
	jle	LBB0_123
## BB#96:                               ##   in Loop: Header=BB0_11 Depth=1
Ltmp196:
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
Ltmp197:
	##DEBUG_VALUE: exec_pipeline:pid <- %EAX
	.loc	1 90 9 is_stmt 0        ## c_posix.c:90:9
	testl	%eax, %eax
Ltmp198:
	.loc	1 105 17 is_stmt 1      ## c_posix.c:105:17
	movq	___stderrp@GOTPCREL(%rip), %rbx
	movq	%rbx, %r13
	.loc	1 105 9 is_stmt 0       ## c_posix.c:105:9
	leaq	L_.str.56(%rip), %rbx
	js	LBB0_97
Ltmp199:
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
	jne	LBB0_100
Ltmp200:
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
	.loc	1 94 5 is_stmt 1        ## c_posix.c:94:5
	movl	-2488(%rbp), %edi       ## 4-byte Reload
Ltmp201:
	movq	-2496(%rbp), %rsi       ## 8-byte Reload
	callq	_exec_nth_command
	jmp	LBB0_100
LBB0_97:                                ## %.thread.i.i
                                        ##   in Loop: Header=BB0_11 Depth=1
Ltmp202:
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
Ltmp203:
	callq	_err_syswarn
Ltmp204:
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
Ltmp205:
	callq	_free
	.loc	1 174 5                 ## c_posix.c:174:5
	movq	-2504(%rbp), %rdi       ## 8-byte Reload
	callq	_free
Ltmp206:
	.loc	1 100 20                ## c_posix.c:100:20
	callq	_getpid
	movl	%eax, %r14d
	jmp	LBB0_102
	.align	4, 0x90
LBB0_101:                               ## %.lr.ph.i.11
                                        ##   in Loop: Header=BB0_102 Depth=2
Ltmp207:
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
	.loc	1 105 17                ## c_posix.c:105:17
	movq	(%r13), %rdi
Ltmp208:
	.loc	1 106 43                ## c_posix.c:106:43
	movl	-192(%rbp), %r8d
	xorl	%eax, %eax
	.loc	1 105 9                 ## c_posix.c:105:9
	movq	%rbx, %rsi
	movl	%r14d, %edx
	callq	_fprintf
Ltmp209:
LBB0_102:                               ## %.lr.ph.i.11
                                        ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	##DEBUG_VALUE: corpse_collector:status <- [%R15+0]
	xorl	%edi, %edi
	xorl	%edx, %edx
	.loc	1 103 22                ## c_posix.c:103:22
	movq	%r15, %rsi
	callq	_waitpid
	movl	%eax, %ecx
Ltmp210:
	##DEBUG_VALUE: corpse_collector:corpse <- %ECX
	.loc	1 103 5 is_stmt 0       ## c_posix.c:103:5
	cmpl	$-1, %ecx
	jne	LBB0_101
Ltmp211:
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
	.loc	1 627 17 is_stmt 1      ## c_posix.c:627:17
	cmpl	$1, %r12d
	jne	LBB0_106
Ltmp212:
## BB#104:                              ## %corpse_collector.exit
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
	jne	LBB0_106
Ltmp213:
## BB#105:                              ##   in Loop: Header=BB0_11 Depth=1
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
Ltmp214:
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
Ltmp215:
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
	.loc	1 650 17 is_stmt 1      ## c_posix.c:650:17
	testl	%r12d, %r12d
	je	LBB0_107
Ltmp216:
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
	.loc	1 675 22                ## c_posix.c:675:22
	cmpl	$1, %r12d
	jne	LBB0_115
Ltmp217:
## BB#114:                              ##   in Loop: Header=BB0_11 Depth=1
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
Ltmp218:
	.loc	1 677 17 is_stmt 0      ## c_posix.c:677:17
	callq	_close
	.loc	1 678 23 is_stmt 1      ## c_posix.c:678:23
	movl	-2276(%rbp), %edi
	.loc	1 678 17 is_stmt 0      ## c_posix.c:678:17
	callq	_close
Ltmp219:
LBB0_115:                               ##   in Loop: Header=BB0_11 Depth=1
	.loc	1 321 25 is_stmt 1      ## c_posix.c:321:25
	leaq	L_.str.28(%rip), %r13
	jmp	LBB0_116
Ltmp220:
LBB0_107:                               ##   in Loop: Header=BB0_11 Depth=1
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
Ltmp221:
	##DEBUG_VALUE: main:status <- undef
	xorl	%edx, %edx
	leaq	-2404(%rbp), %rsi
	.loc	1 652 17 is_stmt 0      ## c_posix.c:652:17
	callq	_waitpid
Ltmp222:
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
Ltmp223:
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
Ltmp224:
	xorl	%eax, %eax
	.loc	1 658 17                ## c_posix.c:658:17
	leaq	L_.str.26(%rip), %rdi
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	callq	_printf
	.loc	1 660 21 is_stmt 1      ## c_posix.c:660:21
	cmpl	$1, _isSignal(%rip)
Ltmp225:
	.loc	1 321 25                ## c_posix.c:321:25
	leaq	L_.str.28(%rip), %r13
	jne	LBB0_116
Ltmp226:
## BB#108:                              ##   in Loop: Header=BB0_11 Depth=1
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
Ltmp227:
	xorl	%edx, %edx
	leaq	-2444(%rbp), %rsi
	callq	_sigprocmask
Ltmp228:
	##DEBUG_VALUE: Janitor:status <- 20
	##DEBUG_VALUE: a <- 0
	.loc	1 672 21                ## c_posix.c:672:21
	movl	$20, -192(%rbp)
	jmp	LBB0_109
	.align	4, 0x90
LBB0_112:                               ##   in Loop: Header=BB0_109 Depth=2
Ltmp229:
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
	xorl	%eax, %eax
	.loc	1 321 25                ## c_posix.c:321:25
Ltmp230:
	movq	%r13, %rdi
Ltmp231:
	movl	%ecx, %esi
	callq	_printf
Ltmp232:
LBB0_109:                               ##   Parent Loop BB0_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
	##DEBUG_VALUE: a <- 1
	.loc	1 308 29                ## c_posix.c:308:29
	movl	$-1, %edi
	movl	$1, %edx
Ltmp233:
	.loc	1 308 29 is_stmt 0      ## c_posix.c:308:29
	movq	%r15, %rsi
	callq	_waitpid
	movl	%eax, %ecx
Ltmp234:
	##DEBUG_VALUE: pid_my1 <- %ECX
	.loc	1 313 17 is_stmt 1      ## c_posix.c:313:17
	testl	%ecx, %ecx
	jle	LBB0_116
Ltmp235:
## BB#110:                              ## %.lr.ph26
                                        ##   in Loop: Header=BB0_109 Depth=2
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
	.loc	1 315 21                ## c_posix.c:315:21
	cmpl	_foreground(%rip), %ecx
	je	LBB0_109
Ltmp236:
## BB#111:                              ##   in Loop: Header=BB0_109 Depth=2
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
	##DEBUG_VALUE: Janitor:status <- [%R15+0]
	.loc	1 319 48                ## c_posix.c:319:48
	movl	-192(%rbp), %eax
	.loc	1 319 25 is_stmt 0      ## c_posix.c:319:25
	andl	$127, %eax
	cmpl	$127, %eax
	je	LBB0_109
	jmp	LBB0_112
Ltmp237:
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
Ltmp238:
	callq	_perror
	jmp	LBB0_69
Ltmp239:
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
Ltmp240:
LBB0_34:                                ##   in Loop: Header=BB0_11 Depth=1
	.loc	1 506 21                ## c_posix.c:506:21
	callq	_perror
	jmp	LBB0_35
Ltmp241:
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
Ltmp242:
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
	addq	$2552, %rsp             ## imm = 0x9F8
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
Ltmp243:
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
	leaq	L_.str.38(%rip), %rdi
Ltmp244:
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp245:
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
	leaq	L_.str.39(%rip), %rdi
Ltmp246:
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp247:
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
Ltmp248:
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
	.loc	1 105 17                ## c_posix.c:105:17
	movq	___stderrp@GOTPCREL(%rip), %r13
Ltmp249:
	.loc	1 520 26                ## c_posix.c:520:26
	leaq	L_.str.17(%rip), %rdi
Ltmp250:
	callq	_getenv
Ltmp251:
	##DEBUG_VALUE: main:pagerValue <- %RAX
	.loc	1 521 17                ## c_posix.c:521:17
	testq	%rax, %rax
	jne	LBB0_40
Ltmp252:
## BB#37:
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
	.loc	1 523 21                ## c_posix.c:523:21
	cmpl	$0, -2532(%rbp)         ## 4-byte Folded Reload
	jne	LBB0_39
Ltmp253:
## BB#38:
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
	leaq	-2336(%rbp), %rbx
	.loc	1 525 34                ## c_posix.c:525:34
Ltmp254:
	leaq	L_.str.3(%rip), %rax
	jmp	LBB0_41
Ltmp255:
LBB0_40:
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
	jmp	LBB0_41
Ltmp256:
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
	leaq	L_.str.40(%rip), %rdi
Ltmp257:
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp258:
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
Ltmp259:
	leaq	L_.str.41(%rip), %rsi
	leaq	L_.str.52(%rip), %rcx
	movl	$88, %edx
	callq	___assert_rtn
Ltmp260:
LBB0_39:
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
	leaq	-2336(%rbp), %rbx
	.loc	1 529 34                ## c_posix.c:529:34
Ltmp261:
	leaq	L_.str.18(%rip), %rax
Ltmp262:
LBB0_41:
	.loc	1 534 30                ## c_posix.c:534:30
	movq	%rax, -2336(%rbp)
Ltmp263:
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
Ltmp264:
	callq	_malloc
Ltmp265:
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
Ltmp266:
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
Ltmp267:
	##DEBUG_VALUE: fork_pipes:i <- 0
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:n <- 4
	leaq	-192(%rbp), %rdi
	.loc	1 277 13                ## c_posix.c:277:13
Ltmp268:
	callq	_pipe
Ltmp269:
	.loc	1 277 13 is_stmt 0      ## c_posix.c:277:13
	cmpl	$-1, %eax
	je	LBB0_119
## BB#42:
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
	##DEBUG_VALUE: fork_pipes:n <- 4
	##DEBUG_VALUE: fork_pipes:in <- 0
	##DEBUG_VALUE: fork_pipes:i <- 0
	.loc	1 282 24 is_stmt 1      ## c_posix.c:282:24
	movl	-188(%rbp), %r14d
	.loc	1 243 16                ## c_posix.c:243:16
Ltmp271:
	callq	_fork
Ltmp272:
	##DEBUG_VALUE: spawn_proc:pid <- %EAX
	.loc	1 243 24 is_stmt 0      ## c_posix.c:243:24
	testl	%eax, %eax
	jne	LBB0_52
Ltmp273:
## BB#43:
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
Ltmp274:
LBB0_48:                                ## %.thread.i
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
	je	LBB0_51
Ltmp275:
## BB#49:
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
Ltmp276:
	callq	_dup2
Ltmp277:
	.loc	1 253 17 is_stmt 0      ## c_posix.c:253:17
	testl	%eax, %eax
	jns	LBB0_50
## BB#120:
Ltmp278:
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
Ltmp279:
	xorl	%eax, %eax
	callq	_err_syserr
Ltmp280:
LBB0_52:
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
Ltmp281:
## BB#53:                               ## %spawn_proc.exit.i
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
Ltmp282:
	.loc	1 283 9 is_stmt 0       ## c_posix.c:283:9
	callq	_close
	.loc	1 284 14 is_stmt 1      ## c_posix.c:284:14
	movl	-192(%rbp), %r15d
Ltmp283:
	##DEBUG_VALUE: fork_pipes:i <- 1
	##DEBUG_VALUE: fork_pipes:in <- %R15D
	leaq	-192(%rbp), %rdi
	.loc	1 277 13                ## c_posix.c:277:13
Ltmp284:
	callq	_pipe
	.loc	1 277 22 is_stmt 0      ## c_posix.c:277:22
	cmpl	$-1, %eax
	je	LBB0_119
Ltmp285:
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
	##DEBUG_VALUE: fork_pipes:in <- %R15D
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 282 24 is_stmt 1      ## c_posix.c:282:24
	movl	-188(%rbp), %r14d
	.loc	1 243 16                ## c_posix.c:243:16
Ltmp286:
	callq	_fork
	movl	$1, %ecx
	.loc	1 243 24 is_stmt 0      ## c_posix.c:243:24
	testl	%eax, %eax
	je	LBB0_44
Ltmp287:
## BB#55:
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
Ltmp288:
## BB#56:                               ## %spawn_proc.exit.1.i
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
Ltmp289:
	.loc	1 283 9 is_stmt 0       ## c_posix.c:283:9
	callq	_close
	.loc	1 284 14 is_stmt 1      ## c_posix.c:284:14
	movl	-192(%rbp), %r15d
	leaq	-192(%rbp), %rdi
	.loc	1 277 13                ## c_posix.c:277:13
Ltmp290:
	callq	_pipe
	.loc	1 277 22 is_stmt 0      ## c_posix.c:277:22
	cmpl	$-1, %eax
	jne	LBB0_57
LBB0_119:
Ltmp291:
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
Ltmp292:
	xorl	%eax, %eax
	callq	_err_syserr
Ltmp293:
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
	.loc	1 255 13                ## c_posix.c:255:13
	movl	%r14d, %edi
Ltmp294:
	callq	_close
Ltmp295:
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
Ltmp296:
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
Ltmp297:
LBB0_63:
	.loc	1 292 5 is_stmt 1       ## c_posix.c:292:5
	leaq	L_.str.32(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_syserr
LBB0_57:
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
	##DEBUG_VALUE: fork_pipes:i <- 1
	.loc	1 282 24                ## c_posix.c:282:24
	movl	-188(%rbp), %r14d
	.loc	1 243 16                ## c_posix.c:243:16
Ltmp299:
	callq	_fork
	movl	$2, %ecx
	.loc	1 243 24 is_stmt 0      ## c_posix.c:243:24
	testl	%eax, %eax
	jne	LBB0_58
Ltmp300:
LBB0_44:
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
Ltmp301:
	testl	%r15d, %r15d
	je	LBB0_48
Ltmp302:
## BB#45:
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
Ltmp303:
	movl	%r15d, %edi
Ltmp304:
	callq	_dup2
Ltmp305:
	.loc	1 247 17 is_stmt 0      ## c_posix.c:247:17
	testl	%eax, %eax
	jns	LBB0_47
## BB#46:
Ltmp306:
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
Ltmp307:
LBB0_61:
	.loc	1 288 9 is_stmt 1       ## c_posix.c:288:9
	leaq	L_.str.30(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_syserr
Ltmp308:
LBB0_47:
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
Ltmp309:
	callq	_close
	jmp	LBB0_48
Ltmp310:
LBB0_58:
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
	jns	LBB0_59
Ltmp311:
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
Ltmp312:
	xorl	%eax, %eax
	callq	_err_syserr
Ltmp313:
LBB0_59:                                ## %spawn_proc.exit.2.i
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
Ltmp314:
	.loc	1 283 9 is_stmt 0       ## c_posix.c:283:9
	callq	_close
	.loc	1 284 14 is_stmt 1      ## c_posix.c:284:14
	movl	-192(%rbp), %edi
	xorl	%esi, %esi
Ltmp315:
	.loc	1 286 9                 ## c_posix.c:286:9
	callq	_dup2
	.loc	1 286 21 is_stmt 0      ## c_posix.c:286:21
	testl	%eax, %eax
Ltmp316:
	.loc	1 286 9                 ## c_posix.c:286:9
	jns	LBB0_62
## BB#60:
Ltmp317:
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
	jmp	LBB0_61
Ltmp318:
LBB0_62:
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
Ltmp319:
	callq	_fprintf
	.loc	1 291 12 is_stmt 1      ## c_posix.c:291:12
	movq	-2336(%rbp), %rdi
	.loc	1 291 5 is_stmt 0       ## c_posix.c:291:5
	movq	%rbx, %rsi
	callq	_execvp
	.loc	1 292 42 is_stmt 1      ## c_posix.c:292:42
	movq	-2336(%rbp), %rsi
	jmp	LBB0_63
Ltmp320:
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
Ltmp321:
	.cfi_def_cfa_offset 16
Ltmp322:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp323:
	.cfi_def_cfa_register %rbp
	##DEBUG_VALUE: sighandler:signo <- %EDI
	##DEBUG_VALUE: sighandler:si <- %RSI
	##DEBUG_VALUE: sighandler:vp <- %RDX
	.loc	1 361 20 prologue_end   ## c_posix.c:361:20
Ltmp324:
	leaq	L_.str.27(%rip), %rsi
	movl	$2, %edi
	movl	$16, %edx
	popq	%rbp
	jmp	_write                  ## TAILCALL
Ltmp325:
Lfunc_end1:
	.cfi_endproc

	.align	4, 0x90
_err_syserr:                            ## @err_syserr
Lfunc_begin2:
	.loc	1 220 0                 ## c_posix.c:220:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp326:
	.cfi_def_cfa_offset 16
Ltmp327:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp328:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	subq	$200, %rsp
Ltmp329:
	.cfi_offset %rbx, -40
Ltmp330:
	.cfi_offset %r14, -32
Ltmp331:
	.cfi_offset %r15, -24
	##DEBUG_VALUE: err_syserr:fmt <- %RDI
	movq	%rdi, %r14
Ltmp332:
	##DEBUG_VALUE: err_syserr:fmt <- %R14
	testb	%al, %al
	je	LBB2_2
Ltmp333:
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
Ltmp334:
LBB2_2:
	##DEBUG_VALUE: err_syserr:fmt <- %R14
	movq	%r9, -184(%rbp)
	movq	%r8, -192(%rbp)
	movq	%rcx, -200(%rbp)
	movq	%rdx, -208(%rbp)
	movq	%rsi, -216(%rbp)
	.loc	1 221 18 prologue_end   ## c_posix.c:221:18
Ltmp335:
	callq	___error
	movl	(%rax), %ebx
Ltmp336:
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
Ltmp337:
	##DEBUG_VALUE: err_syserr:args <- [%RDX+0]
	.loc	1 224 5 is_stmt 0       ## c_posix.c:224:5
	movq	%r14, %rsi
Ltmp338:
	##DEBUG_VALUE: err_syserr:fmt <- %RSI
	callq	_vfprintf
	.loc	1 226 16 is_stmt 1      ## c_posix.c:226:16
Ltmp339:
	testl	%ebx, %ebx
	je	LBB2_4
Ltmp340:
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
Ltmp341:
LBB2_4:
	.loc	1 228 5 is_stmt 1       ## c_posix.c:228:5
	movl	$1, %edi
	callq	_exit
Ltmp342:
Lfunc_end2:
	.cfi_endproc

	.align	4, 0x90
_err_sysexit:                           ## @err_sysexit
Lfunc_begin3:
	.loc	1 203 0                 ## c_posix.c:203:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp343:
	.cfi_def_cfa_offset 16
Ltmp344:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp345:
	.cfi_def_cfa_register %rbp
	subq	$208, %rsp
	##DEBUG_VALUE: err_sysexit:fmt <- %RDI
	testb	%al, %al
	je	LBB3_2
Ltmp346:
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
Ltmp347:
LBB3_2:
	##DEBUG_VALUE: err_sysexit:fmt <- %RDI
	movq	%r9, -168(%rbp)
	movq	%r8, -176(%rbp)
	movq	%rcx, -184(%rbp)
	movq	%rdx, -192(%rbp)
	movq	%rsi, -200(%rbp)
	leaq	-208(%rbp), %rax
	.loc	1 205 5 prologue_end    ## c_posix.c:205:5
Ltmp348:
	movq	%rax, -16(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$48, -28(%rbp)
	movl	$8, -32(%rbp)
	leaq	-32(%rbp), %rsi
Ltmp349:
	##DEBUG_VALUE: err_sysexit:args <- [%RSI+0]
	.loc	1 206 5                 ## c_posix.c:206:5
	callq	_err_vsyswarn
	.loc	1 208 5                 ## c_posix.c:208:5
	movl	$1, %edi
Ltmp350:
	callq	_exit
Ltmp351:
Lfunc_end3:
	.cfi_endproc

	.align	4, 0x90
_err_vsyswarn:                          ## @err_vsyswarn
Lfunc_begin4:
	.loc	1 185 0                 ## c_posix.c:185:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp352:
	.cfi_def_cfa_offset 16
Ltmp353:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp354:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	pushq	%rax
Ltmp355:
	.cfi_offset %rbx, -56
Ltmp356:
	.cfi_offset %r12, -48
Ltmp357:
	.cfi_offset %r13, -40
Ltmp358:
	.cfi_offset %r14, -32
Ltmp359:
	.cfi_offset %r15, -24
	##DEBUG_VALUE: err_vsyswarn:fmt <- %RDI
	##DEBUG_VALUE: err_vsyswarn:args <- %RSI
	movq	%rsi, %r14
Ltmp360:
	##DEBUG_VALUE: err_vsyswarn:args <- %R14
	movq	%rdi, %r15
Ltmp361:
	##DEBUG_VALUE: err_vsyswarn:fmt <- %R15
	.loc	1 186 18 prologue_end   ## c_posix.c:186:18
	callq	___error
	movl	(%rax), %r12d
Ltmp362:
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
	leaq	L_.str.47(%rip), %rsi
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
Ltmp363:
	##DEBUG_VALUE: err_vsyswarn:fmt <- %RSI
	movq	%r14, %rdx
Ltmp364:
	##DEBUG_VALUE: err_vsyswarn:args <- %RDX
	callq	_vfprintf
	.loc	1 189 16 is_stmt 1      ## c_posix.c:189:16
Ltmp365:
	testl	%r12d, %r12d
	je	LBB4_2
Ltmp366:
## BB#1:
	##DEBUG_VALUE: err_vsyswarn:errnum <- %R12D
	.loc	1 190 17                ## c_posix.c:190:17
	movq	(%r13), %rbx
	.loc	1 190 46 is_stmt 0      ## c_posix.c:190:46
	movl	%r12d, %edi
	callq	_strerror
	movq	%rax, %rcx
	.loc	1 190 9                 ## c_posix.c:190:9
	leaq	L_.str.48(%rip), %rsi
	xorl	%eax, %eax
	movq	%rbx, %rdi
	movl	%r12d, %edx
	callq	_fprintf
Ltmp367:
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
Ltmp368:
Lfunc_end4:
	.cfi_endproc

	.align	4, 0x90
_err_syswarn:                           ## @err_syswarn
Lfunc_begin5:
	.loc	1 195 0 is_stmt 1       ## c_posix.c:195:0
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp369:
	.cfi_def_cfa_offset 16
Ltmp370:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp371:
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$216, %rsp
Ltmp372:
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
Ltmp373:
	movq	%rax, -32(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -40(%rbp)
	movl	$48, -44(%rbp)
	movl	$8, -48(%rbp)
	.loc	1 198 5                 ## c_posix.c:198:5
	leaq	L_.str.53(%rip), %rdi
	leaq	-48(%rbp), %rsi
Ltmp374:
	##DEBUG_VALUE: err_syswarn:args <- [%RSI+0]
	callq	_err_vsyswarn
	cmpq	-16(%rbp), %rbx
	jne	LBB5_4
Ltmp375:
## BB#3:
	.loc	1 200 1                 ## c_posix.c:200:1
	addq	$216, %rsp
	popq	%rbx
	popq	%rbp
	retq
Ltmp376:
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
Ltmp377:
	.cfi_def_cfa_offset 16
Ltmp378:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp379:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	pushq	%rax
Ltmp380:
	.cfi_offset %rbx, -40
Ltmp381:
	.cfi_offset %r14, -32
Ltmp382:
	.cfi_offset %r15, -24
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EDI
	##DEBUG_VALUE: exec_nth_command:cmds <- %RSI
	movq	%rsi, %r14
Ltmp383:
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	movl	%edi, %ebx
Ltmp384:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	.loc	1 49 5 prologue_end     ## c_posix.c:49:5
	testl	%ebx, %ebx
	jg	LBB6_1
Ltmp385:
## BB#8:
	leaq	L___func__.exec_nth_command(%rip), %rdi
	leaq	L_.str.41(%rip), %rsi
	leaq	L_.str.52(%rip), %rcx
	movl	$49, %edx
	callq	___assert_rtn
LBB6_1:
Ltmp386:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	.loc	1 50 9                  ## c_posix.c:50:9
	cmpl	$2, %ebx
	jl	LBB6_7
Ltmp387:
## BB#2:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	leaq	-32(%rbp), %rdi
Ltmp388:
	##DEBUG_VALUE: exec_pipe_command:output <- %RDI
	##DEBUG_VALUE: input <- [%RDI+0]
	.loc	1 54 13                 ## c_posix.c:54:13
	callq	_pipe
	.loc	1 54 25 is_stmt 0       ## c_posix.c:54:25
	testl	%eax, %eax
Ltmp389:
	.loc	1 54 13                 ## c_posix.c:54:13
	jne	LBB6_9
Ltmp390:
## BB#3:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	.loc	1 56 20 is_stmt 1       ## c_posix.c:56:20
	callq	_fork
Ltmp391:
	##DEBUG_VALUE: pid <- %EAX
	.loc	1 56 13 is_stmt 0       ## c_posix.c:56:13
	testl	%eax, %eax
	jns	LBB6_4
Ltmp392:
## BB#10:
	.loc	1 57 13 is_stmt 1       ## c_posix.c:57:13
	leaq	L_.str.53(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp393:
LBB6_9:
	.loc	1 55 13                 ## c_posix.c:55:13
	leaq	L_.str.54(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp394:
LBB6_4:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	jne	LBB6_6
Ltmp395:
## BB#5:                                ## %exec_pipe_command.exit
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	.loc	1 61 37                 ## c_posix.c:61:37
	leal	-1(%rbx), %r15d
Ltmp396:
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
Ltmp397:
	##DEBUG_VALUE: exec_pipe_command:cmds <- %R14
	.loc	1 81 5 is_stmt 1        ## c_posix.c:81:5
	movl	%r15d, %edi
	movq	%r14, %rsi
	callq	_exec_nth_command
Ltmp398:
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
Ltmp399:
LBB6_7:
	##DEBUG_VALUE: exec_nth_command:ncmds <- %EBX
	##DEBUG_VALUE: exec_nth_command:cmds <- %R14
	.loc	1 68 12 is_stmt 1       ## c_posix.c:68:12
	movslq	%ebx, %rbx
Ltmp400:
	movq	-8(%r14,%rbx,8), %rsi
	movq	(%rsi), %rdi
	.loc	1 68 5 is_stmt 0        ## c_posix.c:68:5
	callq	_execvp
	.loc	1 69 38 is_stmt 1       ## c_posix.c:69:38
	movq	-8(%r14,%rbx,8), %rax
	movq	(%rax), %rsi
	.loc	1 69 5 is_stmt 0        ## c_posix.c:69:5
	leaq	L_.str.55(%rip), %rdi
	xorl	%eax, %eax
	callq	_err_sysexit
Ltmp401:
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
	.asciz	"Syntax error: pipe before any command"

L_.str.39:                              ## @.str.39
	.asciz	"Syntax error: two pipes with no command between"

L_.str.40:                              ## @.str.40
	.asciz	"Syntax error: pipe with no command following"

L_.str.41:                              ## @.str.41
	.asciz	"c_posix.c"

L_.str.43:                              ## @.str.43
	.asciz	"%s: (%d)"

L_.str.44:                              ## @.str.44
	.asciz	" {%s}"

L_.str.45:                              ## @.str.45
	.asciz	"(null)"

L_.str.47:                              ## @.str.47
	.asciz	"%s:%d: "

L_.str.48:                              ## @.str.48
	.asciz	" (%d: %s)"

L_.str.50:                              ## @.str.50
	.asciz	"cmd [%d]"

L___func__.exec_pipeline:               ## @__func__.exec_pipeline
	.asciz	"exec_pipeline"

L_.str.52:                              ## @.str.52
	.asciz	"ncmds >= 1"

L_.str.53:                              ## @.str.53
	.asciz	"Failed to fork"

L___func__.exec_nth_command:            ## @__func__.exec_nth_command
	.asciz	"exec_nth_command"

L_.str.54:                              ## @.str.54
	.asciz	"Failed to create pipe"

L_.str.55:                              ## @.str.55
	.asciz	"Failed to exec %s"

L_.str.56:                              ## @.str.56
	.asciz	"%d: child %d status 0x%.4X\n"

L_str:                                  ## @str
	.asciz	"malloc failed!"

L_str.57:                               ## @str.57
	.asciz	"SOC"

L_str.58:                               ## @str.58
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
	.asciz	"corpse"                ## string offset=923
	.asciz	"parent"                ## string offset=930
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
Lset34 = Ltmp90-Lfunc_begin0
	.quad	Lset34
Lset35 = Ltmp91-Lfunc_begin0
	.quad	Lset35
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset36 = Ltmp93-Lfunc_begin0
	.quad	Lset36
Lset37 = Ltmp94-Lfunc_begin0
	.quad	Lset37
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset38 = Ltmp98-Lfunc_begin0
	.quad	Lset38
Lset39 = Ltmp99-Lfunc_begin0
	.quad	Lset39
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset40 = Ltmp100-Lfunc_begin0
	.quad	Lset40
Lset41 = Ltmp101-Lfunc_begin0
	.quad	Lset41
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset42 = Ltmp106-Lfunc_begin0
	.quad	Lset42
Lset43 = Ltmp107-Lfunc_begin0
	.quad	Lset43
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset44 = Ltmp109-Lfunc_begin0
	.quad	Lset44
Lset45 = Ltmp124-Lfunc_begin0
	.quad	Lset45
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset46 = Ltmp126-Lfunc_begin0
	.quad	Lset46
Lset47 = Ltmp130-Lfunc_begin0
	.quad	Lset47
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset48 = Ltmp131-Lfunc_begin0
	.quad	Lset48
Lset49 = Ltmp133-Lfunc_begin0
	.quad	Lset49
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset50 = Ltmp134-Lfunc_begin0
	.quad	Lset50
Lset51 = Ltmp138-Lfunc_begin0
	.quad	Lset51
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset52 = Ltmp140-Lfunc_begin0
	.quad	Lset52
Lset53 = Ltmp142-Lfunc_begin0
	.quad	Lset53
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset54 = Ltmp144-Lfunc_begin0
	.quad	Lset54
Lset55 = Ltmp147-Lfunc_begin0
	.quad	Lset55
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset56 = Ltmp150-Lfunc_begin0
	.quad	Lset56
Lset57 = Ltmp151-Lfunc_begin0
	.quad	Lset57
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset58 = Ltmp153-Lfunc_begin0
	.quad	Lset58
Lset59 = Ltmp154-Lfunc_begin0
	.quad	Lset59
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset60 = Ltmp159-Lfunc_begin0
	.quad	Lset60
Lset61 = Ltmp161-Lfunc_begin0
	.quad	Lset61
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset62 = Ltmp163-Lfunc_begin0
	.quad	Lset62
Lset63 = Ltmp178-Lfunc_begin0
	.quad	Lset63
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset64 = Ltmp181-Lfunc_begin0
	.quad	Lset64
Lset65 = Ltmp183-Lfunc_begin0
	.quad	Lset65
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset66 = Ltmp185-Lfunc_begin0
	.quad	Lset66
Lset67 = Ltmp187-Lfunc_begin0
	.quad	Lset67
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset68 = Ltmp188-Lfunc_begin0
	.quad	Lset68
Lset69 = Ltmp189-Lfunc_begin0
	.quad	Lset69
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset70 = Ltmp191-Lfunc_begin0
	.quad	Lset70
Lset71 = Ltmp192-Lfunc_begin0
	.quad	Lset71
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset72 = Ltmp196-Lfunc_begin0
	.quad	Lset72
Lset73 = Ltmp201-Lfunc_begin0
	.quad	Lset73
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset74 = Ltmp202-Lfunc_begin0
	.quad	Lset74
Lset75 = Ltmp205-Lfunc_begin0
	.quad	Lset75
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset76 = Ltmp207-Lfunc_begin0
	.quad	Lset76
Lset77 = Ltmp208-Lfunc_begin0
	.quad	Lset77
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset78 = Ltmp211-Lfunc_begin0
	.quad	Lset78
Lset79 = Ltmp214-Lfunc_begin0
	.quad	Lset79
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset80 = Ltmp215-Lfunc_begin0
	.quad	Lset80
Lset81 = Ltmp218-Lfunc_begin0
	.quad	Lset81
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset82 = Ltmp220-Lfunc_begin0
	.quad	Lset82
Lset83 = Ltmp221-Lfunc_begin0
	.quad	Lset83
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset84 = Ltmp226-Lfunc_begin0
	.quad	Lset84
Lset85 = Ltmp227-Lfunc_begin0
	.quad	Lset85
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset86 = Ltmp229-Lfunc_begin0
	.quad	Lset86
Lset87 = Ltmp231-Lfunc_begin0
	.quad	Lset87
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset88 = Ltmp235-Lfunc_begin0
	.quad	Lset88
Lset89 = Ltmp238-Lfunc_begin0
	.quad	Lset89
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset90 = Ltmp239-Lfunc_begin0
	.quad	Lset90
Lset91 = Ltmp240-Lfunc_begin0
	.quad	Lset91
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset92 = Ltmp241-Lfunc_begin0
	.quad	Lset92
Lset93 = Ltmp244-Lfunc_begin0
	.quad	Lset93
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset94 = Ltmp245-Lfunc_begin0
	.quad	Lset94
Lset95 = Ltmp246-Lfunc_begin0
	.quad	Lset95
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset96 = Ltmp247-Lfunc_begin0
	.quad	Lset96
Lset97 = Ltmp250-Lfunc_begin0
	.quad	Lset97
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset98 = Ltmp252-Lfunc_begin0
	.quad	Lset98
Lset99 = Ltmp257-Lfunc_begin0
	.quad	Lset99
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset100 = Ltmp258-Lfunc_begin0
	.quad	Lset100
Lset101 = Ltmp259-Lfunc_begin0
	.quad	Lset101
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset102 = Ltmp260-Lfunc_begin0
	.quad	Lset102
Lset103 = Ltmp262-Lfunc_begin0
	.quad	Lset103
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset104 = Ltmp263-Lfunc_begin0
	.quad	Lset104
Lset105 = Ltmp264-Lfunc_begin0
	.quad	Lset105
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset106 = Ltmp270-Lfunc_begin0
	.quad	Lset106
Lset107 = Ltmp276-Lfunc_begin0
	.quad	Lset107
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset108 = Ltmp278-Lfunc_begin0
	.quad	Lset108
Lset109 = Ltmp279-Lfunc_begin0
	.quad	Lset109
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset110 = Ltmp280-Lfunc_begin0
	.quad	Lset110
Lset111 = Ltmp282-Lfunc_begin0
	.quad	Lset111
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset112 = Ltmp285-Lfunc_begin0
	.quad	Lset112
Lset113 = Ltmp289-Lfunc_begin0
	.quad	Lset113
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset114 = Ltmp291-Lfunc_begin0
	.quad	Lset114
Lset115 = Ltmp292-Lfunc_begin0
	.quad	Lset115
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset116 = Ltmp293-Lfunc_begin0
	.quad	Lset116
Lset117 = Ltmp294-Lfunc_begin0
	.quad	Lset117
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset118 = Ltmp295-Lfunc_begin0
	.quad	Lset118
Lset119 = Ltmp296-Lfunc_begin0
	.quad	Lset119
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset120 = Ltmp298-Lfunc_begin0
	.quad	Lset120
Lset121 = Ltmp304-Lfunc_begin0
	.quad	Lset121
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset122 = Ltmp306-Lfunc_begin0
	.quad	Lset122
Lset123 = Ltmp307-Lfunc_begin0
	.quad	Lset123
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset124 = Ltmp308-Lfunc_begin0
	.quad	Lset124
Lset125 = Ltmp309-Lfunc_begin0
	.quad	Lset125
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset126 = Ltmp310-Lfunc_begin0
	.quad	Lset126
Lset127 = Ltmp312-Lfunc_begin0
	.quad	Lset127
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset128 = Ltmp313-Lfunc_begin0
	.quad	Lset128
Lset129 = Ltmp314-Lfunc_begin0
	.quad	Lset129
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset130 = Ltmp317-Lfunc_begin0
	.quad	Lset130
Lset131 = Ltmp319-Lfunc_begin0
	.quad	Lset131
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc1:
Lset132 = Lfunc_begin0-Lfunc_begin0
	.quad	Lset132
Lset133 = Ltmp8-Lfunc_begin0
	.quad	Lset133
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
Lset134 = Ltmp8-Lfunc_begin0
	.quad	Lset134
Lset135 = Lfunc_end0-Lfunc_begin0
	.quad	Lset135
	.short	3                       ## Loc expr size
	.byte	118                     ## DW_OP_breg6
	.byte	160                     ## -2528
	.byte	108                     ## 
	.quad	0
	.quad	0
Ldebug_loc2:
Lset136 = Ltmp9-Lfunc_begin0
	.quad	Lset136
Lset137 = Ltmp90-Lfunc_begin0
	.quad	Lset137
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset138 = Ltmp90-Lfunc_begin0
	.quad	Lset138
Lset139 = Ltmp106-Lfunc_begin0
	.quad	Lset139
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset140 = Ltmp106-Lfunc_begin0
	.quad	Lset140
Lset141 = Ltmp239-Lfunc_begin0
	.quad	Lset141
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset142 = Ltmp239-Lfunc_begin0
	.quad	Lset142
Lset143 = Ltmp241-Lfunc_begin0
	.quad	Lset143
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset144 = Ltmp241-Lfunc_begin0
	.quad	Lset144
Lset145 = Ltmp248-Lfunc_begin0
	.quad	Lset145
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset146 = Ltmp248-Lfunc_begin0
	.quad	Lset146
Lset147 = Ltmp256-Lfunc_begin0
	.quad	Lset147
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset148 = Ltmp256-Lfunc_begin0
	.quad	Lset148
Lset149 = Ltmp260-Lfunc_begin0
	.quad	Lset149
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset150 = Ltmp260-Lfunc_begin0
	.quad	Lset150
Lset151 = Lfunc_end0-Lfunc_begin0
	.quad	Lset151
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
	.quad	0
	.quad	0
Ldebug_loc3:
Lset152 = Ltmp9-Lfunc_begin0
	.quad	Lset152
Lset153 = Ltmp111-Lfunc_begin0
	.quad	Lset153
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset154 = Ltmp111-Lfunc_begin0
	.quad	Lset154
Lset155 = Ltmp239-Lfunc_begin0
	.quad	Lset155
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset156 = Ltmp239-Lfunc_begin0
	.quad	Lset156
Lset157 = Ltmp243-Lfunc_begin0
	.quad	Lset157
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset158 = Ltmp243-Lfunc_begin0
	.quad	Lset158
Lset159 = Ltmp247-Lfunc_begin0
	.quad	Lset159
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset160 = Ltmp247-Lfunc_begin0
	.quad	Lset160
Lset161 = Ltmp256-Lfunc_begin0
	.quad	Lset161
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset162 = Ltmp256-Lfunc_begin0
	.quad	Lset162
Lset163 = Ltmp260-Lfunc_begin0
	.quad	Lset163
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset164 = Ltmp260-Lfunc_begin0
	.quad	Lset164
Lset165 = Lfunc_end0-Lfunc_begin0
	.quad	Lset165
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc4:
Lset166 = Ltmp9-Lfunc_begin0
	.quad	Lset166
Lset167 = Ltmp137-Lfunc_begin0
	.quad	Lset167
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset168 = Ltmp137-Lfunc_begin0
	.quad	Lset168
Lset169 = Ltmp237-Lfunc_begin0
	.quad	Lset169
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset170 = Ltmp237-Lfunc_begin0
	.quad	Lset170
Lset171 = Ltmp243-Lfunc_begin0
	.quad	Lset171
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset172 = Ltmp243-Lfunc_begin0
	.quad	Lset172
Lset173 = Ltmp247-Lfunc_begin0
	.quad	Lset173
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset174 = Ltmp247-Lfunc_begin0
	.quad	Lset174
Lset175 = Ltmp256-Lfunc_begin0
	.quad	Lset175
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset176 = Ltmp256-Lfunc_begin0
	.quad	Lset176
Lset177 = Ltmp260-Lfunc_begin0
	.quad	Lset177
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset178 = Ltmp260-Lfunc_begin0
	.quad	Lset178
Lset179 = Lfunc_end0-Lfunc_begin0
	.quad	Lset179
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc5:
Lset180 = Ltmp10-Lfunc_begin0
	.quad	Lset180
Lset181 = Ltmp221-Lfunc_begin0
	.quad	Lset181
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset182 = Ltmp226-Lfunc_begin0
	.quad	Lset182
Lset183 = Ltmp226-Lfunc_begin0
	.quad	Lset183
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset184 = Ltmp229-Lfunc_begin0
	.quad	Lset184
Lset185 = Ltmp229-Lfunc_begin0
	.quad	Lset185
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset186 = Ltmp235-Lfunc_begin0
	.quad	Lset186
Lset187 = Ltmp235-Lfunc_begin0
	.quad	Lset187
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset188 = Ltmp236-Lfunc_begin0
	.quad	Lset188
Lset189 = Ltmp236-Lfunc_begin0
	.quad	Lset189
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset190 = Ltmp237-Lfunc_begin0
	.quad	Lset190
Lset191 = Lfunc_end0-Lfunc_begin0
	.quad	Lset191
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc6:
Lset192 = Ltmp11-Lfunc_begin0
	.quad	Lset192
Lset193 = Ltmp34-Lfunc_begin0
	.quad	Lset193
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset194 = Ltmp34-Lfunc_begin0
	.quad	Lset194
Lset195 = Ltmp36-Lfunc_begin0
	.quad	Lset195
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset196 = Ltmp36-Lfunc_begin0
	.quad	Lset196
Lset197 = Lfunc_end0-Lfunc_begin0
	.quad	Lset197
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc7:
Lset198 = Ltmp12-Lfunc_begin0
	.quad	Lset198
Lset199 = Ltmp127-Lfunc_begin0
	.quad	Lset199
	.short	2                       ## Loc expr size
	.byte	16                      ## DW_OP_constu
	.byte	0                       ## 0
Lset200 = Ltmp127-Lfunc_begin0
	.quad	Lset200
Lset201 = Ltmp128-Lfunc_begin0
	.quad	Lset201
	.short	3                       ## Loc expr size
	.byte	118                     ## DW_OP_breg6
	.byte	172                     ## -2516
	.byte	108                     ## 
Lset202 = Ltmp128-Lfunc_begin0
	.quad	Lset202
Lset203 = Lfunc_end0-Lfunc_begin0
	.quad	Lset203
	.short	2                       ## Loc expr size
	.byte	16                      ## DW_OP_constu
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc8:
Lset204 = Ltmp13-Lfunc_begin0
	.quad	Lset204
Lset205 = Ltmp17-Lfunc_begin0
	.quad	Lset205
	.short	2                       ## Loc expr size
	.byte	116                     ## DW_OP_breg4
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc9:
Lset206 = Ltmp14-Lfunc_begin0
	.quad	Lset206
Lset207 = Ltmp17-Lfunc_begin0
	.quad	Lset207
	.short	2                       ## Loc expr size
	.byte	113                     ## DW_OP_breg1
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc10:
Lset208 = Ltmp16-Lfunc_begin0
	.quad	Lset208
Lset209 = Ltmp26-Lfunc_begin0
	.quad	Lset209
	.short	1                       ## Loc expr size
	.byte	83                      ## DW_OP_reg3
	.quad	0
	.quad	0
Ldebug_loc11:
Lset210 = Ltmp23-Lfunc_begin0
	.quad	Lset210
Lset211 = Ltmp24-Lfunc_begin0
	.quad	Lset211
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
Lset212 = Ltmp24-Lfunc_begin0
	.quad	Lset212
Lset213 = Lfunc_end0-Lfunc_begin0
	.quad	Lset213
	.short	3                       ## Loc expr size
	.byte	118                     ## DW_OP_breg6
	.byte	200                     ## -2488
	.byte	108                     ## 
	.quad	0
	.quad	0
Ldebug_loc12:
Lset214 = Ltmp25-Lfunc_begin0
	.quad	Lset214
Lset215 = Ltmp34-Lfunc_begin0
	.quad	Lset215
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset216 = Ltmp34-Lfunc_begin0
	.quad	Lset216
Lset217 = Ltmp36-Lfunc_begin0
	.quad	Lset217
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset218 = Ltmp36-Lfunc_begin0
	.quad	Lset218
Lset219 = Lfunc_end0-Lfunc_begin0
	.quad	Lset219
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
	.quad	0
	.quad	0
Ldebug_loc13:
Lset220 = Ltmp25-Lfunc_begin0
	.quad	Lset220
Lset221 = Ltmp27-Lfunc_begin0
	.quad	Lset221
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset222 = Ltmp40-Lfunc_begin0
	.quad	Lset222
Lset223 = Ltmp41-Lfunc_begin0
	.quad	Lset223
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
	.quad	0
	.quad	0
Ldebug_loc14:
Lset224 = Ltmp29-Lfunc_begin0
	.quad	Lset224
Lset225 = Ltmp36-Lfunc_begin0
	.quad	Lset225
	.short	1                       ## Loc expr size
	.byte	95                      ## DW_OP_reg15
	.quad	0
	.quad	0
Ldebug_loc15:
Lset226 = Ltmp29-Lfunc_begin0
	.quad	Lset226
Lset227 = Ltmp36-Lfunc_begin0
	.quad	Lset227
	.short	1                       ## Loc expr size
	.byte	95                      ## DW_OP_reg15
	.quad	0
	.quad	0
Ldebug_loc16:
Lset228 = Ltmp33-Lfunc_begin0
	.quad	Lset228
Lset229 = Ltmp36-Lfunc_begin0
	.quad	Lset229
	.short	2                       ## Loc expr size
	.byte	125                     ## DW_OP_breg13
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc17:
Lset230 = Ltmp48-Lfunc_begin0
	.quad	Lset230
Lset231 = Ltmp49-Lfunc_begin0
	.quad	Lset231
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset232 = Ltmp49-Lfunc_begin0
	.quad	Lset232
Lset233 = Ltmp54-Lfunc_begin0
	.quad	Lset233
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
Lset234 = Ltmp54-Lfunc_begin0
	.quad	Lset234
Lset235 = Ltmp54-Lfunc_begin0
	.quad	Lset235
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset236 = Ltmp54-Lfunc_begin0
	.quad	Lset236
Lset237 = Ltmp55-Lfunc_begin0
	.quad	Lset237
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
Lset238 = Ltmp55-Lfunc_begin0
	.quad	Lset238
Lset239 = Ltmp55-Lfunc_begin0
	.quad	Lset239
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset240 = Ltmp55-Lfunc_begin0
	.quad	Lset240
Lset241 = Ltmp56-Lfunc_begin0
	.quad	Lset241
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc18:
Lset242 = Ltmp53-Lfunc_begin0
	.quad	Lset242
Lset243 = Ltmp54-Lfunc_begin0
	.quad	Lset243
	.short	3                       ## Loc expr size
	.byte	82                      ## super-register DW_OP_reg2
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc19:
Lset244 = Ltmp59-Lfunc_begin0
	.quad	Lset244
Lset245 = Ltmp60-Lfunc_begin0
	.quad	Lset245
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset246 = Ltmp60-Lfunc_begin0
	.quad	Lset246
Lset247 = Ltmp66-Lfunc_begin0
	.quad	Lset247
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
Lset248 = Ltmp66-Lfunc_begin0
	.quad	Lset248
Lset249 = Ltmp66-Lfunc_begin0
	.quad	Lset249
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset250 = Ltmp66-Lfunc_begin0
	.quad	Lset250
Lset251 = Ltmp67-Lfunc_begin0
	.quad	Lset251
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
Lset252 = Ltmp67-Lfunc_begin0
	.quad	Lset252
Lset253 = Ltmp67-Lfunc_begin0
	.quad	Lset253
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset254 = Ltmp67-Lfunc_begin0
	.quad	Lset254
Lset255 = Ltmp68-Lfunc_begin0
	.quad	Lset255
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc20:
Lset256 = Ltmp65-Lfunc_begin0
	.quad	Lset256
Lset257 = Ltmp66-Lfunc_begin0
	.quad	Lset257
	.short	3                       ## Loc expr size
	.byte	82                      ## super-register DW_OP_reg2
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc21:
Lset258 = Ltmp75-Lfunc_begin0
	.quad	Lset258
Lset259 = Ltmp77-Lfunc_begin0
	.quad	Lset259
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc22:
Lset260 = Ltmp82-Lfunc_begin0
	.quad	Lset260
Lset261 = Ltmp84-Lfunc_begin0
	.quad	Lset261
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc23:
Lset262 = Ltmp95-Lfunc_begin0
	.quad	Lset262
Lset263 = Ltmp96-Lfunc_begin0
	.quad	Lset263
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc24:
Lset264 = Ltmp102-Lfunc_begin0
	.quad	Lset264
Lset265 = Ltmp104-Lfunc_begin0
	.quad	Lset265
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc25:
Lset266 = Ltmp103-Lfunc_begin0
	.quad	Lset266
Lset267 = Ltmp106-Lfunc_begin0
	.quad	Lset267
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
	.quad	0
	.quad	0
Ldebug_loc26:
Lset268 = Ltmp131-Lfunc_begin0
	.quad	Lset268
Lset269 = Ltmp132-Lfunc_begin0
	.quad	Lset269
	.short	4                       ## Loc expr size
	.byte	16                      ## DW_OP_constu
	.byte	128                     ## 524288
	.byte	128                     ## 
	.byte	32                      ## 
	.quad	0
	.quad	0
Ldebug_loc27:
Lset270 = Ltmp139-Lfunc_begin0
	.quad	Lset270
Lset271 = Ltmp140-Lfunc_begin0
	.quad	Lset271
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
Lset272 = Ltmp143-Lfunc_begin0
	.quad	Lset272
Lset273 = Ltmp144-Lfunc_begin0
	.quad	Lset273
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc28:
Lset274 = Ltmp156-Lfunc_begin0
	.quad	Lset274
Lset275 = Ltmp163-Lfunc_begin0
	.quad	Lset275
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset276 = Ltmp163-Lfunc_begin0
	.quad	Lset276
Lset277 = Ltmp164-Lfunc_begin0
	.quad	Lset277
	.short	3                       ## Loc expr size
	.byte	94                      ## super-register DW_OP_reg14
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset278 = Ltmp165-Lfunc_begin0
	.quad	Lset278
Lset279 = Lfunc_end0-Lfunc_begin0
	.quad	Lset279
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc29:
Lset280 = Ltmp156-Lfunc_begin0
	.quad	Lset280
Lset281 = Ltmp170-Lfunc_begin0
	.quad	Lset281
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset282 = Ltmp170-Lfunc_begin0
	.quad	Lset282
Lset283 = Ltmp171-Lfunc_begin0
	.quad	Lset283
	.short	3                       ## Loc expr size
	.byte	118                     ## DW_OP_breg6
	.byte	200                     ## -2488
	.byte	108                     ## 
Lset284 = Ltmp171-Lfunc_begin0
	.quad	Lset284
Lset285 = Ltmp172-Lfunc_begin0
	.quad	Lset285
	.short	3                       ## Loc expr size
	.byte	81                      ## super-register DW_OP_reg1
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset286 = Ltmp173-Lfunc_begin0
	.quad	Lset286
Lset287 = Lfunc_end0-Lfunc_begin0
	.quad	Lset287
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
	.quad	0
	.quad	0
Ldebug_loc30:
Lset288 = Ltmp160-Lfunc_begin0
	.quad	Lset288
Lset289 = Ltmp165-Lfunc_begin0
	.quad	Lset289
	.short	1                       ## Loc expr size
	.byte	93                      ## DW_OP_reg13
	.quad	0
	.quad	0
Ldebug_loc31:
Lset290 = Ltmp184-Lfunc_begin0
	.quad	Lset290
Lset291 = Ltmp186-Lfunc_begin0
	.quad	Lset291
	.short	1                       ## Loc expr size
	.byte	83                      ## DW_OP_reg3
	.quad	0
	.quad	0
Ldebug_loc32:
Lset292 = Ltmp197-Lfunc_begin0
	.quad	Lset292
Lset293 = Ltmp199-Lfunc_begin0
	.quad	Lset293
	.short	3                       ## Loc expr size
	.byte	80                      ## super-register DW_OP_reg0
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc33:
Lset294 = Ltmp209-Lfunc_begin0
	.quad	Lset294
Lset295 = Ltmp211-Lfunc_begin0
	.quad	Lset295
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc34:
Lset296 = Ltmp210-Lfunc_begin0
	.quad	Lset296
Lset297 = Ltmp211-Lfunc_begin0
	.quad	Lset297
	.short	3                       ## Loc expr size
	.byte	82                      ## super-register DW_OP_reg2
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc35:
Lset298 = Ltmp223-Lfunc_begin0
	.quad	Lset298
Lset299 = Ltmp224-Lfunc_begin0
	.quad	Lset299
	.short	1                       ## Loc expr size
	.byte	82                      ## DW_OP_reg2
	.quad	0
	.quad	0
Ldebug_loc36:
Lset300 = Ltmp228-Lfunc_begin0
	.quad	Lset300
Lset301 = Ltmp229-Lfunc_begin0
	.quad	Lset301
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset302 = Ltmp229-Lfunc_begin0
	.quad	Lset302
Lset303 = Ltmp235-Lfunc_begin0
	.quad	Lset303
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
Lset304 = Ltmp235-Lfunc_begin0
	.quad	Lset304
Lset305 = Ltmp235-Lfunc_begin0
	.quad	Lset305
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset306 = Ltmp235-Lfunc_begin0
	.quad	Lset306
Lset307 = Ltmp236-Lfunc_begin0
	.quad	Lset307
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
Lset308 = Ltmp236-Lfunc_begin0
	.quad	Lset308
Lset309 = Ltmp236-Lfunc_begin0
	.quad	Lset309
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	20                      ## 20
Lset310 = Ltmp236-Lfunc_begin0
	.quad	Lset310
Lset311 = Ltmp237-Lfunc_begin0
	.quad	Lset311
	.short	2                       ## Loc expr size
	.byte	127                     ## DW_OP_breg15
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc37:
Lset312 = Ltmp234-Lfunc_begin0
	.quad	Lset312
Lset313 = Ltmp235-Lfunc_begin0
	.quad	Lset313
	.short	3                       ## Loc expr size
	.byte	82                      ## super-register DW_OP_reg2
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc38:
Lset314 = Ltmp251-Lfunc_begin0
	.quad	Lset314
Lset315 = Ltmp252-Lfunc_begin0
	.quad	Lset315
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
Lset316 = Ltmp255-Lfunc_begin0
	.quad	Lset316
Lset317 = Ltmp256-Lfunc_begin0
	.quad	Lset317
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc39:
Lset318 = Ltmp265-Lfunc_begin0
	.quad	Lset318
Lset319 = Ltmp266-Lfunc_begin0
	.quad	Lset319
	.short	1                       ## Loc expr size
	.byte	80                      ## DW_OP_reg0
	.quad	0
	.quad	0
Ldebug_loc40:
Lset320 = Ltmp267-Lfunc_begin0
	.quad	Lset320
Lset321 = Ltmp283-Lfunc_begin0
	.quad	Lset321
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset322 = Ltmp283-Lfunc_begin0
	.quad	Lset322
Lset323 = Ltmp291-Lfunc_begin0
	.quad	Lset323
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset324 = Ltmp291-Lfunc_begin0
	.quad	Lset324
Lset325 = Ltmp298-Lfunc_begin0
	.quad	Lset325
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset326 = Ltmp298-Lfunc_begin0
	.quad	Lset326
Lset327 = Ltmp311-Lfunc_begin0
	.quad	Lset327
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
Lset328 = Ltmp311-Lfunc_begin0
	.quad	Lset328
Lset329 = Ltmp313-Lfunc_begin0
	.quad	Lset329
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset330 = Ltmp313-Lfunc_begin0
	.quad	Lset330
Lset331 = Lfunc_end0-Lfunc_begin0
	.quad	Lset331
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	1                       ## 1
	.quad	0
	.quad	0
Ldebug_loc41:
Lset332 = Ltmp267-Lfunc_begin0
	.quad	Lset332
Lset333 = Ltmp283-Lfunc_begin0
	.quad	Lset333
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
Lset334 = Ltmp283-Lfunc_begin0
	.quad	Lset334
Lset335 = Ltmp287-Lfunc_begin0
	.quad	Lset335
	.short	3                       ## Loc expr size
	.byte	95                      ## super-register DW_OP_reg15
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset336 = Ltmp291-Lfunc_begin0
	.quad	Lset336
Lset337 = Lfunc_end0-Lfunc_begin0
	.quad	Lset337
	.short	2                       ## Loc expr size
	.byte	17                      ## DW_OP_consts
	.byte	0                       ## 0
	.quad	0
	.quad	0
Ldebug_loc42:
Lset338 = Ltmp272-Lfunc_begin0
	.quad	Lset338
Lset339 = Ltmp273-Lfunc_begin0
	.quad	Lset339
	.short	3                       ## Loc expr size
	.byte	80                      ## super-register DW_OP_reg0
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc43:
Lset340 = Lfunc_begin2-Lfunc_begin0
	.quad	Lset340
Lset341 = Ltmp332-Lfunc_begin0
	.quad	Lset341
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
Lset342 = Ltmp332-Lfunc_begin0
	.quad	Lset342
Lset343 = Ltmp338-Lfunc_begin0
	.quad	Lset343
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset344 = Ltmp338-Lfunc_begin0
	.quad	Lset344
Lset345 = Ltmp340-Lfunc_begin0
	.quad	Lset345
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
	.quad	0
	.quad	0
Ldebug_loc44:
Lset346 = Ltmp336-Lfunc_begin0
	.quad	Lset346
Lset347 = Ltmp341-Lfunc_begin0
	.quad	Lset347
	.short	3                       ## Loc expr size
	.byte	83                      ## super-register DW_OP_reg3
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc45:
Lset348 = Lfunc_begin3-Lfunc_begin0
	.quad	Lset348
Lset349 = Ltmp350-Lfunc_begin0
	.quad	Lset349
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
	.quad	0
	.quad	0
Ldebug_loc46:
Lset350 = Lfunc_begin4-Lfunc_begin0
	.quad	Lset350
Lset351 = Ltmp361-Lfunc_begin0
	.quad	Lset351
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
Lset352 = Ltmp361-Lfunc_begin0
	.quad	Lset352
Lset353 = Ltmp363-Lfunc_begin0
	.quad	Lset353
	.short	1                       ## Loc expr size
	.byte	95                      ## DW_OP_reg15
Lset354 = Ltmp363-Lfunc_begin0
	.quad	Lset354
Lset355 = Ltmp366-Lfunc_begin0
	.quad	Lset355
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
	.quad	0
	.quad	0
Ldebug_loc47:
Lset356 = Lfunc_begin4-Lfunc_begin0
	.quad	Lset356
Lset357 = Ltmp360-Lfunc_begin0
	.quad	Lset357
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
Lset358 = Ltmp360-Lfunc_begin0
	.quad	Lset358
Lset359 = Ltmp364-Lfunc_begin0
	.quad	Lset359
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset360 = Ltmp364-Lfunc_begin0
	.quad	Lset360
Lset361 = Ltmp366-Lfunc_begin0
	.quad	Lset361
	.short	1                       ## Loc expr size
	.byte	81                      ## DW_OP_reg1
	.quad	0
	.quad	0
Ldebug_loc48:
Lset362 = Ltmp362-Lfunc_begin0
	.quad	Lset362
Lset363 = Ltmp367-Lfunc_begin0
	.quad	Lset363
	.short	3                       ## Loc expr size
	.byte	92                      ## super-register DW_OP_reg12
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc49:
Lset364 = Lfunc_begin6-Lfunc_begin0
	.quad	Lset364
Lset365 = Ltmp384-Lfunc_begin0
	.quad	Lset365
	.short	3                       ## Loc expr size
	.byte	85                      ## super-register DW_OP_reg5
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset366 = Ltmp384-Lfunc_begin0
	.quad	Lset366
Lset367 = Ltmp385-Lfunc_begin0
	.quad	Lset367
	.short	3                       ## Loc expr size
	.byte	83                      ## super-register DW_OP_reg3
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset368 = Ltmp386-Lfunc_begin0
	.quad	Lset368
Lset369 = Ltmp392-Lfunc_begin0
	.quad	Lset369
	.short	3                       ## Loc expr size
	.byte	83                      ## super-register DW_OP_reg3
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
Lset370 = Ltmp394-Lfunc_begin0
	.quad	Lset370
Lset371 = Ltmp400-Lfunc_begin0
	.quad	Lset371
	.short	3                       ## Loc expr size
	.byte	83                      ## super-register DW_OP_reg3
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc50:
Lset372 = Lfunc_begin6-Lfunc_begin0
	.quad	Lset372
Lset373 = Ltmp383-Lfunc_begin0
	.quad	Lset373
	.short	1                       ## Loc expr size
	.byte	84                      ## DW_OP_reg4
Lset374 = Ltmp383-Lfunc_begin0
	.quad	Lset374
Lset375 = Ltmp385-Lfunc_begin0
	.quad	Lset375
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset376 = Ltmp386-Lfunc_begin0
	.quad	Lset376
Lset377 = Ltmp392-Lfunc_begin0
	.quad	Lset377
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
Lset378 = Ltmp394-Lfunc_begin0
	.quad	Lset378
Lset379 = Lfunc_end6-Lfunc_begin0
	.quad	Lset379
	.short	1                       ## Loc expr size
	.byte	94                      ## DW_OP_reg14
	.quad	0
	.quad	0
Ldebug_loc51:
Lset380 = Ltmp388-Lfunc_begin0
	.quad	Lset380
Lset381 = Ltmp390-Lfunc_begin0
	.quad	Lset381
	.short	1                       ## Loc expr size
	.byte	85                      ## DW_OP_reg5
	.quad	0
	.quad	0
Ldebug_loc52:
Lset382 = Ltmp391-Lfunc_begin0
	.quad	Lset382
Lset383 = Ltmp392-Lfunc_begin0
	.quad	Lset383
	.short	3                       ## Loc expr size
	.byte	80                      ## super-register DW_OP_reg0
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc53:
Lset384 = Ltmp396-Lfunc_begin0
	.quad	Lset384
Lset385 = Ltmp398-Lfunc_begin0
	.quad	Lset385
	.short	3                       ## Loc expr size
	.byte	95                      ## super-register DW_OP_reg15
	.byte	147                     ## DW_OP_piece
	.byte	4                       ## 4
	.quad	0
	.quad	0
Ldebug_loc54:
Lset386 = Ltmp397-Lfunc_begin0
	.quad	Lset386
Lset387 = Ltmp398-Lfunc_begin0
	.quad	Lset387
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
	.long	4139                    ## Length of Unit
	.short	2                       ## DWARF version number
Lset388 = Lsection_abbrev-Lsection_abbrev ## Offset Into Abbrev. Section
	.long	Lset388
	.byte	8                       ## Address Size (in bytes)
	.byte	1                       ## Abbrev [1] 0xb:0x1024 DW_TAG_compile_unit
	.long	0                       ## DW_AT_producer
	.short	12                      ## DW_AT_language
	.long	42                      ## DW_AT_name
Lset389 = Lline_table_start0-Lsection_line ## DW_AT_stmt_list
	.long	Lset389
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
	.long	728                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	102                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x502:0xb DW_TAG_variable
	.long	923                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	101                     ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	21                      ## Abbrev [21] 0x50d:0xb DW_TAG_variable
	.long	930                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	100                     ## DW_AT_decl_line
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
	.byte	23                      ## Abbrev [23] 0x5ce:0x500 DW_TAG_subprogram
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
Lset390 = Ldebug_loc0-Lsection_debug_loc ## DW_AT_location
	.long	Lset390
	.long	759                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	365                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	24                      ## Abbrev [24] 0x5ff:0x10 DW_TAG_formal_parameter
Lset391 = Ldebug_loc1-Lsection_debug_loc ## DW_AT_location
	.long	Lset391
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
	.long	3340                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x61f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\240v"
	.long	1105                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	369                     ## DW_AT_decl_line
	.long	3352                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x62f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\240n"
	.long	1110                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	370                     ## DW_AT_decl_line
	.long	3352                    ## DW_AT_type
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
	.long	3365                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x65f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\360m"
	.long	1125                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	382                     ## DW_AT_decl_line
	.long	3365                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x66f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\340m"
	.long	1130                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	383                     ## DW_AT_decl_line
	.long	3365                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x67f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\300m"
	.long	1140                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	384                     ## DW_AT_decl_line
	.long	3340                    ## DW_AT_type
	.byte	25                      ## Abbrev [25] 0x68f:0x10 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\240m"
	.long	1145                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	397                     ## DW_AT_decl_line
	.long	3377                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x69f:0x10 DW_TAG_variable
Lset392 = Ldebug_loc2-Lsection_debug_loc ## DW_AT_location
	.long	Lset392
	.long	1150                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	379                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x6af:0x10 DW_TAG_variable
Lset393 = Ldebug_loc3-Lsection_debug_loc ## DW_AT_location
	.long	Lset393
	.long	1167                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	378                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x6bf:0x10 DW_TAG_variable
Lset394 = Ldebug_loc4-Lsection_debug_loc ## DW_AT_location
	.long	Lset394
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
Lset395 = Ldebug_loc5-Lsection_debug_loc ## DW_AT_location
	.long	Lset395
	.long	728                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	386                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x6ec:0x10 DW_TAG_variable
Lset396 = Ldebug_loc6-Lsection_debug_loc ## DW_AT_location
	.long	Lset396
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
Lset397 = Ldebug_loc7-Lsection_debug_loc ## DW_AT_location
	.long	Lset397
	.long	1208                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	401                     ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x734:0x10 DW_TAG_variable
Lset398 = Ldebug_loc8-Lsection_debug_loc ## DW_AT_location
	.long	Lset398
	.long	1217                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	407                     ## DW_AT_decl_line
	.long	3389                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x744:0x10 DW_TAG_variable
Lset399 = Ldebug_loc9-Lsection_debug_loc ## DW_AT_location
	.long	Lset399
	.long	1452                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	407                     ## DW_AT_decl_line
	.long	3389                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x754:0x10 DW_TAG_variable
Lset400 = Ldebug_loc10-Lsection_debug_loc ## DW_AT_location
	.long	Lset400
	.long	1456                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	404                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x764:0x10 DW_TAG_variable
Lset401 = Ldebug_loc11-Lsection_debug_loc ## DW_AT_location
	.long	Lset401
	.long	1466                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	405                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x774:0x10 DW_TAG_variable
Lset402 = Ldebug_loc12-Lsection_debug_loc ## DW_AT_location
	.long	Lset402
	.long	1477                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	403                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x784:0x10 DW_TAG_variable
Lset403 = Ldebug_loc13-Lsection_debug_loc ## DW_AT_location
	.long	Lset403
	.long	1481                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	374                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x794:0x10 DW_TAG_variable
Lset404 = Ldebug_loc14-Lsection_debug_loc ## DW_AT_location
	.long	Lset404
	.long	1488                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	391                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7a4:0x10 DW_TAG_variable
Lset405 = Ldebug_loc22-Lsection_debug_loc ## DW_AT_location
	.long	Lset405
	.long	1496                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	373                     ## DW_AT_decl_line
	.long	3752                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7b4:0x10 DW_TAG_variable
Lset406 = Ldebug_loc23-Lsection_debug_loc ## DW_AT_location
	.long	Lset406
	.long	1526                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	376                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7c4:0x10 DW_TAG_variable
Lset407 = Ldebug_loc24-Lsection_debug_loc ## DW_AT_location
	.long	Lset407
	.long	1535                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	394                     ## DW_AT_decl_line
	.long	3774                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7d4:0x10 DW_TAG_variable
Lset408 = Ldebug_loc25-Lsection_debug_loc ## DW_AT_location
	.long	Lset408
	.long	1631                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	395                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x7e4:0xc DW_TAG_variable
	.long	1639                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	398                     ## DW_AT_decl_line
	.long	3928                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x7f0:0x10 DW_TAG_variable
Lset409 = Ldebug_loc26-Lsection_debug_loc ## DW_AT_location
	.long	Lset409
	.long	1694                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	400                     ## DW_AT_decl_line
	.long	3730                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x800:0x10 DW_TAG_variable
Lset410 = Ldebug_loc27-Lsection_debug_loc ## DW_AT_location
	.long	Lset410
	.long	1701                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	367                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x810:0xc DW_TAG_variable
	.long	1703                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	399                     ## DW_AT_decl_line
	.long	3928                    ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x81c:0x10 DW_TAG_variable
Lset411 = Ldebug_loc35-Lsection_debug_loc ## DW_AT_location
	.long	Lset411
	.long	1712                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	385                     ## DW_AT_decl_line
	.long	719                     ## DW_AT_type
	.byte	26                      ## Abbrev [26] 0x82c:0x10 DW_TAG_variable
Lset412 = Ldebug_loc38-Lsection_debug_loc ## DW_AT_location
	.long	Lset412
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
Lset413 = Ldebug_loc39-Lsection_debug_loc ## DW_AT_location
	.long	Lset413
	.long	1730                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	390                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0x859:0xc DW_TAG_variable
	.long	1734                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	371                     ## DW_AT_decl_line
	.long	3976                    ## DW_AT_type
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
	.long	3988                    ## DW_AT_type
	.byte	28                      ## Abbrev [28] 0x889:0x1f DW_TAG_inlined_subroutine
	.long	175                     ## DW_AT_abstract_origin
Lset414 = Ldebug_ranges0-Ldebug_range   ## DW_AT_ranges
	.long	Lset414
	.byte	1                       ## DW_AT_call_file
	.short	437                     ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0x895:0x9 DW_TAG_formal_parameter
Lset415 = Ldebug_loc15-Lsection_debug_loc ## DW_AT_location
	.long	Lset415
	.long	190                     ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0x89e:0x9 DW_TAG_variable
Lset416 = Ldebug_loc16-Lsection_debug_loc ## DW_AT_location
	.long	Lset416
	.long	202                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	28                      ## Abbrev [28] 0x8a8:0x31 DW_TAG_inlined_subroutine
	.long	829                     ## DW_AT_abstract_origin
Lset417 = Ldebug_ranges1-Ldebug_range   ## DW_AT_ranges
	.long	Lset417
	.byte	1                       ## DW_AT_call_file
	.short	461                     ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0x8b4:0x9 DW_TAG_formal_parameter
Lset418 = Ldebug_loc17-Lsection_debug_loc ## DW_AT_location
	.long	Lset418
	.long	840                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x8bd:0x1b DW_TAG_lexical_block
Lset419 = Ldebug_ranges3-Ldebug_range   ## DW_AT_ranges
	.long	Lset419
	.byte	32                      ## Abbrev [32] 0x8c2:0x6 DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	853                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x8c8:0xf DW_TAG_lexical_block
Lset420 = Ldebug_ranges2-Ldebug_range   ## DW_AT_ranges
	.long	Lset420
	.byte	30                      ## Abbrev [30] 0x8cd:0x9 DW_TAG_variable
Lset421 = Ldebug_loc18-Lsection_debug_loc ## DW_AT_location
	.long	Lset421
	.long	866                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	28                      ## Abbrev [28] 0x8d9:0x8e DW_TAG_inlined_subroutine
	.long	943                     ## DW_AT_abstract_origin
Lset422 = Ldebug_ranges4-Ldebug_range   ## DW_AT_ranges
	.long	Lset422
	.byte	1                       ## DW_AT_call_file
	.short	624                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0x8e5:0x9 DW_TAG_variable
Lset423 = Ldebug_loc28-Lsection_debug_loc ## DW_AT_location
	.long	Lset423
	.long	975                     ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0x8ee:0x9 DW_TAG_variable
Lset424 = Ldebug_loc29-Lsection_debug_loc ## DW_AT_location
	.long	Lset424
	.long	986                     ## DW_AT_abstract_origin
	.byte	33                      ## Abbrev [33] 0x8f7:0x18 DW_TAG_inlined_subroutine
	.long	881                     ## DW_AT_abstract_origin
Lset425 = Ldebug_ranges5-Ldebug_range   ## DW_AT_ranges
	.long	Lset425
	.byte	1                       ## DW_AT_call_file
	.byte	140                     ## DW_AT_call_line
	.byte	31                      ## Abbrev [31] 0x902:0xc DW_TAG_lexical_block
Lset426 = Ldebug_ranges6-Ldebug_range   ## DW_AT_ranges
	.long	Lset426
	.byte	32                      ## Abbrev [32] 0x907:0x6 DW_TAG_variable
	.byte	0                       ## DW_AT_const_value
	.long	925                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	31                      ## Abbrev [31] 0x90f:0x1b DW_TAG_lexical_block
Lset427 = Ldebug_ranges8-Ldebug_range   ## DW_AT_ranges
	.long	Lset427
	.byte	32                      ## Abbrev [32] 0x914:0x6 DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	1020                    ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x91a:0xf DW_TAG_lexical_block
Lset428 = Ldebug_ranges7-Ldebug_range   ## DW_AT_ranges
	.long	Lset428
	.byte	30                      ## Abbrev [30] 0x91f:0x9 DW_TAG_variable
Lset429 = Ldebug_loc30-Lsection_debug_loc ## DW_AT_location
	.long	Lset429
	.long	1032                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	33                      ## Abbrev [33] 0x92a:0x27 DW_TAG_inlined_subroutine
	.long	1158                    ## DW_AT_abstract_origin
Lset430 = Ldebug_ranges9-Ldebug_range   ## DW_AT_ranges
	.long	Lset430
	.byte	1                       ## DW_AT_call_file
	.byte	171                     ## DW_AT_call_line
	.byte	31                      ## Abbrev [31] 0x935:0x1b DW_TAG_lexical_block
Lset431 = Ldebug_ranges11-Ldebug_range  ## DW_AT_ranges
	.long	Lset431
	.byte	32                      ## Abbrev [32] 0x93a:0x6 DW_TAG_variable
	.byte	0                       ## DW_AT_const_value
	.long	1191                    ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x940:0xf DW_TAG_lexical_block
Lset432 = Ldebug_ranges10-Ldebug_range  ## DW_AT_ranges
	.long	Lset432
	.byte	30                      ## Abbrev [30] 0x945:0x9 DW_TAG_variable
Lset433 = Ldebug_loc31-Lsection_debug_loc ## DW_AT_location
	.long	Lset433
	.long	1203                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	33                      ## Abbrev [33] 0x951:0x15 DW_TAG_inlined_subroutine
	.long	1217                    ## DW_AT_abstract_origin
Lset434 = Ldebug_ranges12-Ldebug_range  ## DW_AT_ranges
	.long	Lset434
	.byte	1                       ## DW_AT_call_file
	.byte	172                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0x95c:0x9 DW_TAG_variable
Lset435 = Ldebug_loc32-Lsection_debug_loc ## DW_AT_location
	.long	Lset435
	.long	1249                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	34                      ## Abbrev [34] 0x967:0x18 DW_TAG_inlined_subroutine
	.long	1136                    ## DW_AT_abstract_origin
	.quad	Ltmp136                 ## DW_AT_low_pc
	.quad	Ltmp137                 ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	612                     ## DW_AT_call_line
	.byte	28                      ## Abbrev [28] 0x97f:0x1f DW_TAG_inlined_subroutine
	.long	1261                    ## DW_AT_abstract_origin
Lset436 = Ldebug_ranges13-Ldebug_range  ## DW_AT_ranges
	.long	Lset436
	.byte	1                       ## DW_AT_call_file
	.short	625                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0x98b:0x9 DW_TAG_variable
Lset437 = Ldebug_loc33-Lsection_debug_loc ## DW_AT_location
	.long	Lset437
	.long	1271                    ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0x994:0x9 DW_TAG_variable
Lset438 = Ldebug_loc34-Lsection_debug_loc ## DW_AT_location
	.long	Lset438
	.long	1282                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	31                      ## Abbrev [31] 0x99e:0x44 DW_TAG_lexical_block
Lset439 = Ldebug_ranges17-Ldebug_range  ## DW_AT_ranges
	.long	Lset439
	.byte	27                      ## Abbrev [27] 0x9a3:0xd DW_TAG_variable
	.byte	0                       ## DW_AT_const_value
	.long	735                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	662                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	28                      ## Abbrev [28] 0x9b0:0x31 DW_TAG_inlined_subroutine
	.long	829                     ## DW_AT_abstract_origin
Lset440 = Ldebug_ranges14-Ldebug_range  ## DW_AT_ranges
	.long	Lset440
	.byte	1                       ## DW_AT_call_file
	.short	672                     ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0x9bc:0x9 DW_TAG_formal_parameter
Lset441 = Ldebug_loc36-Lsection_debug_loc ## DW_AT_location
	.long	Lset441
	.long	840                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x9c5:0x1b DW_TAG_lexical_block
Lset442 = Ldebug_ranges16-Ldebug_range  ## DW_AT_ranges
	.long	Lset442
	.byte	32                      ## Abbrev [32] 0x9ca:0x6 DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	853                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x9d0:0xf DW_TAG_lexical_block
Lset443 = Ldebug_ranges15-Ldebug_range  ## DW_AT_ranges
	.long	Lset443
	.byte	30                      ## Abbrev [30] 0x9d5:0x9 DW_TAG_variable
Lset444 = Ldebug_loc37-Lsection_debug_loc ## DW_AT_location
	.long	Lset444
	.long	866                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	28                      ## Abbrev [28] 0x9e2:0x31 DW_TAG_inlined_subroutine
	.long	829                     ## DW_AT_abstract_origin
Lset445 = Ldebug_ranges18-Ldebug_range  ## DW_AT_ranges
	.long	Lset445
	.byte	1                       ## DW_AT_call_file
	.short	469                     ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0x9ee:0x9 DW_TAG_formal_parameter
Lset446 = Ldebug_loc19-Lsection_debug_loc ## DW_AT_location
	.long	Lset446
	.long	840                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0x9f7:0x1b DW_TAG_lexical_block
Lset447 = Ldebug_ranges20-Ldebug_range  ## DW_AT_ranges
	.long	Lset447
	.byte	32                      ## Abbrev [32] 0x9fc:0x6 DW_TAG_variable
	.byte	1                       ## DW_AT_const_value
	.long	853                     ## DW_AT_abstract_origin
	.byte	31                      ## Abbrev [31] 0xa02:0xf DW_TAG_lexical_block
Lset448 = Ldebug_ranges19-Ldebug_range  ## DW_AT_ranges
	.long	Lset448
	.byte	30                      ## Abbrev [30] 0xa07:0x9 DW_TAG_variable
Lset449 = Ldebug_loc20-Lsection_debug_loc ## DW_AT_location
	.long	Lset449
	.long	866                     ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	28                      ## Abbrev [28] 0xa13:0x16 DW_TAG_inlined_subroutine
	.long	1051                    ## DW_AT_abstract_origin
Lset450 = Ldebug_ranges21-Ldebug_range  ## DW_AT_ranges
	.long	Lset450
	.byte	1                       ## DW_AT_call_file
	.short	471                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0xa1f:0x9 DW_TAG_variable
Lset451 = Ldebug_loc21-Lsection_debug_loc ## DW_AT_location
	.long	Lset451
	.long	1074                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	34                      ## Abbrev [34] 0xa29:0x18 DW_TAG_inlined_subroutine
	.long	1099                    ## DW_AT_abstract_origin
	.quad	Ltmp79                  ## DW_AT_low_pc
	.quad	Ltmp80                  ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	472                     ## DW_AT_call_line
	.byte	35                      ## Abbrev [35] 0xa41:0x1e DW_TAG_inlined_subroutine
	.long	1099                    ## DW_AT_abstract_origin
	.quad	Ltmp86                  ## DW_AT_low_pc
	.quad	Ltmp88                  ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	486                     ## DW_AT_call_line
	.byte	36                      ## Abbrev [36] 0xa59:0x5 DW_TAG_formal_parameter
	.long	1124                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	35                      ## Abbrev [35] 0xa5f:0x1e DW_TAG_inlined_subroutine
	.long	1099                    ## DW_AT_abstract_origin
	.quad	Ltmp106                 ## DW_AT_low_pc
	.quad	Ltmp108                 ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	516                     ## DW_AT_call_line
	.byte	36                      ## Abbrev [36] 0xa77:0x5 DW_TAG_formal_parameter
	.long	1124                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	35                      ## Abbrev [35] 0xa7d:0x50 DW_TAG_inlined_subroutine
	.long	1305                    ## DW_AT_abstract_origin
	.quad	Ltmp268                 ## DW_AT_low_pc
	.quad	Ltmp320                 ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.short	564                     ## DW_AT_call_line
	.byte	37                      ## Abbrev [37] 0xa95:0x6 DW_TAG_formal_parameter
	.byte	4                       ## DW_AT_const_value
	.long	1316                    ## DW_AT_abstract_origin
	.byte	38                      ## Abbrev [38] 0xa9b:0x9 DW_TAG_variable
	.byte	3                       ## DW_AT_location
	.byte	145
	.ascii	"\300~"
	.long	1340                    ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0xaa4:0x9 DW_TAG_variable
Lset452 = Ldebug_loc40-Lsection_debug_loc ## DW_AT_location
	.long	Lset452
	.long	1352                    ## DW_AT_abstract_origin
	.byte	30                      ## Abbrev [30] 0xaad:0x9 DW_TAG_variable
Lset453 = Ldebug_loc41-Lsection_debug_loc ## DW_AT_location
	.long	Lset453
	.long	1364                    ## DW_AT_abstract_origin
	.byte	28                      ## Abbrev [28] 0xab6:0x16 DW_TAG_inlined_subroutine
	.long	1427                    ## DW_AT_abstract_origin
Lset454 = Ldebug_ranges22-Ldebug_range  ## DW_AT_ranges
	.long	Lset454
	.byte	1                       ## DW_AT_call_file
	.short	282                     ## DW_AT_call_line
	.byte	30                      ## Abbrev [30] 0xac2:0x9 DW_TAG_variable
Lset455 = Ldebug_loc42-Lsection_debug_loc ## DW_AT_location
	.long	Lset455
	.long	1474                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	39                      ## Abbrev [39] 0xace:0x55 DW_TAG_subprogram
	.quad	Lfunc_begin1            ## DW_AT_low_pc
	.quad	Lfunc_end1              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	988                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	358                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	40                      ## Abbrev [40] 0xaea:0x10 DW_TAG_formal_parameter
	.byte	3                       ## DW_AT_location
	.byte	85
	.byte	147
	.byte	4
	.long	1747                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	358                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	40                      ## Abbrev [40] 0xafa:0xe DW_TAG_formal_parameter
	.byte	1                       ## DW_AT_location
	.byte	84
	.long	1753                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	358                     ## DW_AT_decl_line
	.long	4000                    ## DW_AT_type
	.byte	40                      ## Abbrev [40] 0xb08:0xe DW_TAG_formal_parameter
	.byte	1                       ## DW_AT_location
	.byte	81
	.long	1766                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	358                     ## DW_AT_decl_line
	.long	169                     ## DW_AT_type
	.byte	11                      ## Abbrev [11] 0xb16:0xc DW_TAG_variable
	.long	1769                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.short	360                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	41                      ## Abbrev [41] 0xb23:0x49 DW_TAG_subprogram
	.quad	Lfunc_begin2            ## DW_AT_low_pc
	.quad	Lfunc_end2              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	999                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	219                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	42                      ## Abbrev [42] 0xb3e:0xf DW_TAG_formal_parameter
Lset456 = Ldebug_loc43-Lsection_debug_loc ## DW_AT_location
	.long	Lset456
	.long	1891                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	219                     ## DW_AT_decl_line
	.long	170                     ## DW_AT_type
	.byte	43                      ## Abbrev [43] 0xb4d:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	80
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.long	4016                    ## DW_AT_type
	.byte	44                      ## Abbrev [44] 0xb5b:0xf DW_TAG_variable
Lset457 = Ldebug_loc44-Lsection_debug_loc ## DW_AT_location
	.long	Lset457
	.long	1895                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	221                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	45                      ## Abbrev [45] 0xb6a:0x1 DW_TAG_unspecified_parameters
	.byte	0                       ## End Of Children Mark
	.byte	41                      ## Abbrev [41] 0xb6c:0x3a DW_TAG_subprogram
	.quad	Lfunc_begin3            ## DW_AT_low_pc
	.quad	Lfunc_end3              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	1010                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	202                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	42                      ## Abbrev [42] 0xb87:0xf DW_TAG_formal_parameter
Lset458 = Ldebug_loc45-Lsection_debug_loc ## DW_AT_location
	.long	Lset458
	.long	1891                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	202                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	43                      ## Abbrev [43] 0xb96:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	96
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	204                     ## DW_AT_decl_line
	.long	4016                    ## DW_AT_type
	.byte	45                      ## Abbrev [45] 0xba4:0x1 DW_TAG_unspecified_parameters
	.byte	0                       ## End Of Children Mark
	.byte	41                      ## Abbrev [41] 0xba6:0x49 DW_TAG_subprogram
	.quad	Lfunc_begin4            ## DW_AT_low_pc
	.quad	Lfunc_end4              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	1022                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	184                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	42                      ## Abbrev [42] 0xbc1:0xf DW_TAG_formal_parameter
Lset459 = Ldebug_loc46-Lsection_debug_loc ## DW_AT_location
	.long	Lset459
	.long	1891                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	184                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	42                      ## Abbrev [42] 0xbd0:0xf DW_TAG_formal_parameter
Lset460 = Ldebug_loc47-Lsection_debug_loc ## DW_AT_location
	.long	Lset460
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	184                     ## DW_AT_decl_line
	.long	4126                    ## DW_AT_type
	.byte	44                      ## Abbrev [44] 0xbdf:0xf DW_TAG_variable
Lset461 = Ldebug_loc48-Lsection_debug_loc ## DW_AT_location
	.long	Lset461
	.long	1895                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	186                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	41                      ## Abbrev [41] 0xbef:0x36 DW_TAG_subprogram
	.quad	Lfunc_begin5            ## DW_AT_low_pc
	.quad	Lfunc_end5              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	1035                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	194                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	20                      ## Abbrev [20] 0xc0a:0xb DW_TAG_formal_parameter
	.long	1891                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	194                     ## DW_AT_decl_line
	.long	152                     ## DW_AT_type
	.byte	43                      ## Abbrev [43] 0xc15:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	80
	.long	801                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	196                     ## DW_AT_decl_line
	.long	4016                    ## DW_AT_type
	.byte	45                      ## Abbrev [45] 0xc23:0x1 DW_TAG_unspecified_parameters
	.byte	0                       ## End Of Children Mark
	.byte	19                      ## Abbrev [19] 0xc25:0x2c DW_TAG_subprogram
	.long	1047                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	1                       ## DW_AT_inline
	.byte	20                      ## Abbrev [20] 0xc2f:0xb DW_TAG_formal_parameter
	.long	891                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0xc3a:0xb DW_TAG_formal_parameter
	.long	897                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.long	1046                    ## DW_AT_type
	.byte	20                      ## Abbrev [20] 0xc45:0xb DW_TAG_formal_parameter
	.long	1065                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.long	3153                    ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xc51:0x5 DW_TAG_pointer_type
	.long	69                      ## DW_AT_type
	.byte	41                      ## Abbrev [41] 0xc56:0x9c DW_TAG_subprogram
	.quad	Lfunc_begin6            ## DW_AT_low_pc
	.quad	Lfunc_end6              ## DW_AT_high_pc
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	1072                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	47                      ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	42                      ## Abbrev [42] 0xc71:0xf DW_TAG_formal_parameter
Lset462 = Ldebug_loc49-Lsection_debug_loc ## DW_AT_location
	.long	Lset462
	.long	891                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	47                      ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	42                      ## Abbrev [42] 0xc80:0xf DW_TAG_formal_parameter
Lset463 = Ldebug_loc50-Lsection_debug_loc ## DW_AT_location
	.long	Lset463
	.long	897                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	47                      ## DW_AT_decl_line
	.long	1046                    ## DW_AT_type
	.byte	46                      ## Abbrev [46] 0xc8f:0x62 DW_TAG_lexical_block
	.quad	Ltmp388                 ## DW_AT_low_pc
	.quad	Ltmp399                 ## DW_AT_high_pc
	.byte	43                      ## Abbrev [43] 0xca0:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	96
	.long	1902                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	53                      ## DW_AT_decl_line
	.long	4131                    ## DW_AT_type
	.byte	44                      ## Abbrev [44] 0xcae:0xf DW_TAG_variable
Lset464 = Ldebug_loc52-Lsection_debug_loc ## DW_AT_location
	.long	Lset464
	.long	902                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	52                      ## DW_AT_decl_line
	.long	98                      ## DW_AT_type
	.byte	47                      ## Abbrev [47] 0xcbd:0x33 DW_TAG_inlined_subroutine
	.long	3109                    ## DW_AT_abstract_origin
	.quad	Ltmp396                 ## DW_AT_low_pc
	.quad	Ltmp398                 ## DW_AT_high_pc
	.byte	1                       ## DW_AT_call_file
	.byte	61                      ## DW_AT_call_line
	.byte	29                      ## Abbrev [29] 0xcd4:0x9 DW_TAG_formal_parameter
Lset465 = Ldebug_loc53-Lsection_debug_loc ## DW_AT_location
	.long	Lset465
	.long	3119                    ## DW_AT_abstract_origin
	.byte	29                      ## Abbrev [29] 0xcdd:0x9 DW_TAG_formal_parameter
Lset466 = Ldebug_loc54-Lsection_debug_loc ## DW_AT_location
	.long	Lset466
	.long	3130                    ## DW_AT_abstract_origin
	.byte	29                      ## Abbrev [29] 0xce6:0x9 DW_TAG_formal_parameter
Lset467 = Ldebug_loc51-Lsection_debug_loc ## DW_AT_location
	.long	Lset467
	.long	3141                    ## DW_AT_abstract_origin
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	0                       ## End Of Children Mark
	.byte	48                      ## Abbrev [48] 0xcf2:0x1a DW_TAG_subprogram
	.long	1089                    ## DW_AT_name
	.byte	15                      ## DW_AT_decl_file
	.byte	114                     ## DW_AT_decl_line
	.byte	1                       ## DW_AT_prototyped
	.long	69                      ## DW_AT_type
	.byte	1                       ## DW_AT_external
	.byte	1                       ## DW_AT_APPLE_optimized
	.byte	20                      ## Abbrev [20] 0xd00:0xb DW_TAG_formal_parameter
	.long	1913                    ## DW_AT_name
	.byte	15                      ## DW_AT_decl_file
	.byte	114                     ## DW_AT_decl_line
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xd0c:0xc DW_TAG_array_type
	.long	170                     ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xd11:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	4                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xd18:0xd DW_TAG_array_type
	.long	162                     ## DW_AT_type
	.byte	49                      ## Abbrev [49] 0xd1d:0x7 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.short	1024                    ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xd25:0xc DW_TAG_array_type
	.long	170                     ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xd2a:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	2                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xd31:0xc DW_TAG_array_type
	.long	1382                    ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xd36:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	4                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	50                      ## Abbrev [50] 0xd3d:0x37 DW_TAG_structure_type
	.long	1220                    ## DW_AT_name
	.byte	16                      ## DW_AT_byte_size
	.byte	16                      ## DW_AT_decl_file
	.short	286                     ## DW_AT_decl_line
	.byte	51                      ## Abbrev [51] 0xd46:0xf DW_TAG_member
	.long	1230                    ## DW_AT_name
	.long	3444                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	287                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	51                      ## Abbrev [51] 0xd55:0xf DW_TAG_member
	.long	1408                    ## DW_AT_name
	.long	3730                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	288                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	51                      ## Abbrev [51] 0xd64:0xf DW_TAG_member
	.long	1443                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	289                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	12
	.byte	0                       ## End Of Children Mark
	.byte	52                      ## Abbrev [52] 0xd74:0x28 DW_TAG_union_type
	.long	1230                    ## DW_AT_name
	.byte	8                       ## DW_AT_byte_size
	.byte	16                      ## DW_AT_decl_file
	.short	269                     ## DW_AT_decl_line
	.byte	51                      ## Abbrev [51] 0xd7d:0xf DW_TAG_member
	.long	1244                    ## DW_AT_name
	.long	3484                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	270                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	51                      ## Abbrev [51] 0xd8c:0xf DW_TAG_member
	.long	1257                    ## DW_AT_name
	.long	3497                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.short	271                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xd9c:0x5 DW_TAG_pointer_type
	.long	3489                    ## DW_AT_type
	.byte	53                      ## Abbrev [53] 0xda1:0x8 DW_TAG_subroutine_type
	.byte	1                       ## DW_AT_prototyped
	.byte	54                      ## Abbrev [54] 0xda3:0x5 DW_TAG_formal_parameter
	.long	69                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xda9:0x5 DW_TAG_pointer_type
	.long	3502                    ## DW_AT_type
	.byte	53                      ## Abbrev [53] 0xdae:0x12 DW_TAG_subroutine_type
	.byte	1                       ## DW_AT_prototyped
	.byte	54                      ## Abbrev [54] 0xdb0:0x5 DW_TAG_formal_parameter
	.long	69                      ## DW_AT_type
	.byte	54                      ## Abbrev [54] 0xdb5:0x5 DW_TAG_formal_parameter
	.long	3520                    ## DW_AT_type
	.byte	54                      ## Abbrev [54] 0xdba:0x5 DW_TAG_formal_parameter
	.long	169                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xdc0:0x5 DW_TAG_pointer_type
	.long	3525                    ## DW_AT_type
	.byte	12                      ## Abbrev [12] 0xdc5:0x95 DW_TAG_structure_type
	.long	1272                    ## DW_AT_name
	.byte	104                     ## DW_AT_byte_size
	.byte	16                      ## DW_AT_decl_file
	.byte	177                     ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xdcd:0xe DW_TAG_member
	.long	1282                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	178                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xddb:0xe DW_TAG_member
	.long	1291                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	179                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	13                      ## Abbrev [13] 0xde9:0xe DW_TAG_member
	.long	1300                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	180                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	13                      ## Abbrev [13] 0xdf7:0xe DW_TAG_member
	.long	1308                    ## DW_AT_name
	.long	98                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	181                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	12
	.byte	13                      ## Abbrev [13] 0xe05:0xe DW_TAG_member
	.long	1315                    ## DW_AT_name
	.long	635                     ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	182                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	16
	.byte	13                      ## Abbrev [13] 0xe13:0xe DW_TAG_member
	.long	1322                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	183                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	20
	.byte	13                      ## Abbrev [13] 0xe21:0xe DW_TAG_member
	.long	1332                    ## DW_AT_name
	.long	169                     ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	184                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	24
	.byte	13                      ## Abbrev [13] 0xe2f:0xe DW_TAG_member
	.long	1340                    ## DW_AT_name
	.long	3674                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	185                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	32
	.byte	13                      ## Abbrev [13] 0xe3d:0xe DW_TAG_member
	.long	1376                    ## DW_AT_name
	.long	719                     ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	186                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	40
	.byte	13                      ## Abbrev [13] 0xe4b:0xe DW_TAG_member
	.long	1384                    ## DW_AT_name
	.long	3711                    ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	187                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	48
	.byte	0                       ## End Of Children Mark
	.byte	55                      ## Abbrev [55] 0xe5a:0x25 DW_TAG_union_type
	.long	1349                    ## DW_AT_name
	.byte	8                       ## DW_AT_byte_size
	.byte	16                      ## DW_AT_decl_file
	.byte	158                     ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xe62:0xe DW_TAG_member
	.long	1356                    ## DW_AT_name
	.long	69                      ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	160                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xe70:0xe DW_TAG_member
	.long	1366                    ## DW_AT_name
	.long	169                     ## DW_AT_type
	.byte	16                      ## DW_AT_decl_file
	.byte	161                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xe7f:0xc DW_TAG_array_type
	.long	3723                    ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xe84:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	7                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	3                       ## Abbrev [3] 0xe8b:0x7 DW_TAG_base_type
	.long	1390                    ## DW_AT_name
	.byte	7                       ## DW_AT_encoding
	.byte	8                       ## DW_AT_byte_size
	.byte	4                       ## Abbrev [4] 0xe92:0xb DW_TAG_typedef
	.long	3741                    ## DW_AT_type
	.long	1416                    ## DW_AT_name
	.byte	17                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xe9d:0xb DW_TAG_typedef
	.long	657                     ## DW_AT_type
	.long	1425                    ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	73                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xea8:0xb DW_TAG_typedef
	.long	3763                    ## DW_AT_type
	.long	1503                    ## DW_AT_name
	.byte	18                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xeb3:0xb DW_TAG_typedef
	.long	3723                    ## DW_AT_type
	.long	1510                    ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	92                      ## DW_AT_decl_line
	.byte	6                       ## Abbrev [6] 0xebe:0x5 DW_TAG_pointer_type
	.long	3779                    ## DW_AT_type
	.byte	12                      ## Abbrev [12] 0xec3:0x95 DW_TAG_structure_type
	.long	1538                    ## DW_AT_name
	.byte	72                      ## DW_AT_byte_size
	.byte	19                      ## DW_AT_decl_file
	.byte	84                      ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xecb:0xe DW_TAG_member
	.long	1545                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	85                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xed9:0xe DW_TAG_member
	.long	1553                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	86                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	13                      ## Abbrev [13] 0xee7:0xe DW_TAG_member
	.long	1563                    ## DW_AT_name
	.long	635                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	87                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	16
	.byte	13                      ## Abbrev [13] 0xef5:0xe DW_TAG_member
	.long	1570                    ## DW_AT_name
	.long	675                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	88                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	20
	.byte	13                      ## Abbrev [13] 0xf03:0xe DW_TAG_member
	.long	1577                    ## DW_AT_name
	.long	708                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	89                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	24
	.byte	13                      ## Abbrev [13] 0xf11:0xe DW_TAG_member
	.long	1587                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	90                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	32
	.byte	13                      ## Abbrev [13] 0xf1f:0xe DW_TAG_member
	.long	1596                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	91                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	40
	.byte	13                      ## Abbrev [13] 0xf2d:0xe DW_TAG_member
	.long	1605                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	92                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	48
	.byte	13                      ## Abbrev [13] 0xf3b:0xe DW_TAG_member
	.long	1612                    ## DW_AT_name
	.long	170                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	93                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	56
	.byte	13                      ## Abbrev [13] 0xf49:0xe DW_TAG_member
	.long	1621                    ## DW_AT_name
	.long	708                     ## DW_AT_type
	.byte	19                      ## DW_AT_decl_file
	.byte	94                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	64
	.byte	0                       ## End Of Children Mark
	.byte	12                      ## Abbrev [12] 0xf58:0x25 DW_TAG_structure_type
	.long	1650                    ## DW_AT_name
	.byte	16                      ## DW_AT_byte_size
	.byte	20                      ## DW_AT_decl_file
	.byte	30                      ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xf60:0xe DW_TAG_member
	.long	1658                    ## DW_AT_name
	.long	708                     ## DW_AT_type
	.byte	20                      ## DW_AT_decl_file
	.byte	32                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xf6e:0xe DW_TAG_member
	.long	1665                    ## DW_AT_name
	.long	3965                    ## DW_AT_type
	.byte	20                      ## DW_AT_decl_file
	.byte	33                      ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	0                       ## End Of Children Mark
	.byte	4                       ## Abbrev [4] 0xf7d:0xb DW_TAG_typedef
	.long	120                     ## DW_AT_type
	.long	1673                    ## DW_AT_name
	.byte	3                       ## DW_AT_decl_file
	.byte	74                      ## DW_AT_decl_line
	.byte	14                      ## Abbrev [14] 0xf88:0xc DW_TAG_array_type
	.long	170                     ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xf8d:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	100                     ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	14                      ## Abbrev [14] 0xf94:0xc DW_TAG_array_type
	.long	1382                    ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xf99:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	3                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xfa0:0x5 DW_TAG_pointer_type
	.long	4005                    ## DW_AT_type
	.byte	4                       ## Abbrev [4] 0xfa5:0xb DW_TAG_typedef
	.long	3525                    ## DW_AT_type
	.long	1756                    ## DW_AT_name
	.byte	16                      ## DW_AT_decl_file
	.byte	188                     ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xfb0:0xb DW_TAG_typedef
	.long	4027                    ## DW_AT_type
	.long	1782                    ## DW_AT_name
	.byte	21                      ## DW_AT_decl_file
	.byte	31                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xfbb:0xb DW_TAG_typedef
	.long	4038                    ## DW_AT_type
	.long	1790                    ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	98                      ## DW_AT_decl_line
	.byte	4                       ## Abbrev [4] 0xfc6:0xb DW_TAG_typedef
	.long	4049                    ## DW_AT_type
	.long	1807                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	14                      ## Abbrev [14] 0xfd1:0xc DW_TAG_array_type
	.long	4061                    ## DW_AT_type
	.byte	15                      ## Abbrev [15] 0xfd6:0x6 DW_TAG_subrange_type
	.long	822                     ## DW_AT_type
	.byte	1                       ## DW_AT_count
	.byte	0                       ## End Of Children Mark
	.byte	12                      ## Abbrev [12] 0xfdd:0x41 DW_TAG_structure_type
	.long	1825                    ## DW_AT_name
	.byte	24                      ## DW_AT_byte_size
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	13                      ## Abbrev [13] 0xfe5:0xe DW_TAG_member
	.long	1839                    ## DW_AT_name
	.long	668                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	13                      ## Abbrev [13] 0xff3:0xe DW_TAG_member
	.long	1849                    ## DW_AT_name
	.long	668                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	13                      ## Abbrev [13] 0x1001:0xe DW_TAG_member
	.long	1859                    ## DW_AT_name
	.long	169                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	13                      ## Abbrev [13] 0x100f:0xe DW_TAG_member
	.long	1877                    ## DW_AT_name
	.long	169                     ## DW_AT_type
	.byte	1                       ## DW_AT_decl_file
	.byte	222                     ## DW_AT_decl_line
	.byte	2                       ## DW_AT_data_member_location
	.byte	35
	.byte	16
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0x101e:0x5 DW_TAG_pointer_type
	.long	4061                    ## DW_AT_type
	.byte	4                       ## Abbrev [4] 0x1023:0xb DW_TAG_typedef
	.long	1415                    ## DW_AT_type
	.long	1908                    ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	41                      ## DW_AT_decl_line
	.byte	0                       ## End Of Children Mark
	.section	__DWARF,__debug_ranges,regular,debug
Ldebug_range:
Ldebug_ranges0:
Lset468 = Ltmp33-Lfunc_begin0
	.quad	Lset468
Lset469 = Ltmp34-Lfunc_begin0
	.quad	Lset469
Lset470 = Ltmp35-Lfunc_begin0
	.quad	Lset470
Lset471 = Ltmp36-Lfunc_begin0
	.quad	Lset471
	.quad	0
	.quad	0
Ldebug_ranges1:
Lset472 = Ltmp44-Lfunc_begin0
	.quad	Lset472
Lset473 = Ltmp45-Lfunc_begin0
	.quad	Lset473
Lset474 = Ltmp50-Lfunc_begin0
	.quad	Lset474
Lset475 = Ltmp56-Lfunc_begin0
	.quad	Lset475
Lset476 = Ltmp63-Lfunc_begin0
	.quad	Lset476
Lset477 = Ltmp64-Lfunc_begin0
	.quad	Lset477
Lset478 = Ltmp219-Lfunc_begin0
	.quad	Lset478
Lset479 = Ltmp220-Lfunc_begin0
	.quad	Lset479
Lset480 = Ltmp225-Lfunc_begin0
	.quad	Lset480
Lset481 = Ltmp226-Lfunc_begin0
	.quad	Lset481
Lset482 = Ltmp232-Lfunc_begin0
	.quad	Lset482
Lset483 = Ltmp233-Lfunc_begin0
	.quad	Lset483
	.quad	0
	.quad	0
Ldebug_ranges2:
Lset484 = Ltmp44-Lfunc_begin0
	.quad	Lset484
Lset485 = Ltmp45-Lfunc_begin0
	.quad	Lset485
Lset486 = Ltmp50-Lfunc_begin0
	.quad	Lset486
Lset487 = Ltmp56-Lfunc_begin0
	.quad	Lset487
Lset488 = Ltmp63-Lfunc_begin0
	.quad	Lset488
Lset489 = Ltmp64-Lfunc_begin0
	.quad	Lset489
Lset490 = Ltmp219-Lfunc_begin0
	.quad	Lset490
Lset491 = Ltmp220-Lfunc_begin0
	.quad	Lset491
Lset492 = Ltmp225-Lfunc_begin0
	.quad	Lset492
Lset493 = Ltmp226-Lfunc_begin0
	.quad	Lset493
Lset494 = Ltmp232-Lfunc_begin0
	.quad	Lset494
Lset495 = Ltmp233-Lfunc_begin0
	.quad	Lset495
	.quad	0
	.quad	0
Ldebug_ranges3:
Lset496 = Ltmp44-Lfunc_begin0
	.quad	Lset496
Lset497 = Ltmp45-Lfunc_begin0
	.quad	Lset497
Lset498 = Ltmp50-Lfunc_begin0
	.quad	Lset498
Lset499 = Ltmp56-Lfunc_begin0
	.quad	Lset499
Lset500 = Ltmp63-Lfunc_begin0
	.quad	Lset500
Lset501 = Ltmp64-Lfunc_begin0
	.quad	Lset501
Lset502 = Ltmp219-Lfunc_begin0
	.quad	Lset502
Lset503 = Ltmp220-Lfunc_begin0
	.quad	Lset503
Lset504 = Ltmp225-Lfunc_begin0
	.quad	Lset504
Lset505 = Ltmp226-Lfunc_begin0
	.quad	Lset505
Lset506 = Ltmp232-Lfunc_begin0
	.quad	Lset506
Lset507 = Ltmp233-Lfunc_begin0
	.quad	Lset507
	.quad	0
	.quad	0
Ldebug_ranges4:
Lset508 = Ltmp45-Lfunc_begin0
	.quad	Lset508
Lset509 = Ltmp46-Lfunc_begin0
	.quad	Lset509
Lset510 = Ltmp146-Lfunc_begin0
	.quad	Lset510
Lset511 = Ltmp198-Lfunc_begin0
	.quad	Lset511
Lset512 = Ltmp200-Lfunc_begin0
	.quad	Lset512
Lset513 = Ltmp206-Lfunc_begin0
	.quad	Lset513
Lset514 = Ltmp243-Lfunc_begin0
	.quad	Lset514
Lset515 = Ltmp247-Lfunc_begin0
	.quad	Lset515
Lset516 = Ltmp256-Lfunc_begin0
	.quad	Lset516
Lset517 = Ltmp260-Lfunc_begin0
	.quad	Lset517
	.quad	0
	.quad	0
Ldebug_ranges5:
Lset518 = Ltmp45-Lfunc_begin0
	.quad	Lset518
Lset519 = Ltmp46-Lfunc_begin0
	.quad	Lset519
Lset520 = Ltmp146-Lfunc_begin0
	.quad	Lset520
Lset521 = Ltmp155-Lfunc_begin0
	.quad	Lset521
Lset522 = Ltmp180-Lfunc_begin0
	.quad	Lset522
Lset523 = Ltmp181-Lfunc_begin0
	.quad	Lset523
Lset524 = Ltmp188-Lfunc_begin0
	.quad	Lset524
Lset525 = Ltmp189-Lfunc_begin0
	.quad	Lset525
Lset526 = Ltmp193-Lfunc_begin0
	.quad	Lset526
Lset527 = Ltmp194-Lfunc_begin0
	.quad	Lset527
	.quad	0
	.quad	0
Ldebug_ranges6:
Lset528 = Ltmp45-Lfunc_begin0
	.quad	Lset528
Lset529 = Ltmp46-Lfunc_begin0
	.quad	Lset529
Lset530 = Ltmp148-Lfunc_begin0
	.quad	Lset530
Lset531 = Ltmp153-Lfunc_begin0
	.quad	Lset531
Lset532 = Ltmp180-Lfunc_begin0
	.quad	Lset532
Lset533 = Ltmp181-Lfunc_begin0
	.quad	Lset533
	.quad	0
	.quad	0
Ldebug_ranges7:
Lset534 = Ltmp159-Lfunc_begin0
	.quad	Lset534
Lset535 = Ltmp173-Lfunc_begin0
	.quad	Lset535
Lset536 = Ltmp243-Lfunc_begin0
	.quad	Lset536
Lset537 = Ltmp247-Lfunc_begin0
	.quad	Lset537
	.quad	0
	.quad	0
Ldebug_ranges8:
Lset538 = Ltmp158-Lfunc_begin0
	.quad	Lset538
Lset539 = Ltmp175-Lfunc_begin0
	.quad	Lset539
Lset540 = Ltmp243-Lfunc_begin0
	.quad	Lset540
Lset541 = Ltmp247-Lfunc_begin0
	.quad	Lset541
	.quad	0
	.quad	0
Ldebug_ranges9:
Lset542 = Ltmp177-Lfunc_begin0
	.quad	Lset542
Lset543 = Ltmp180-Lfunc_begin0
	.quad	Lset543
Lset544 = Ltmp182-Lfunc_begin0
	.quad	Lset544
Lset545 = Ltmp188-Lfunc_begin0
	.quad	Lset545
Lset546 = Ltmp189-Lfunc_begin0
	.quad	Lset546
Lset547 = Ltmp193-Lfunc_begin0
	.quad	Lset547
Lset548 = Ltmp194-Lfunc_begin0
	.quad	Lset548
Lset549 = Ltmp195-Lfunc_begin0
	.quad	Lset549
	.quad	0
	.quad	0
Ldebug_ranges10:
Lset550 = Ltmp182-Lfunc_begin0
	.quad	Lset550
Lset551 = Ltmp188-Lfunc_begin0
	.quad	Lset551
Lset552 = Ltmp189-Lfunc_begin0
	.quad	Lset552
Lset553 = Ltmp190-Lfunc_begin0
	.quad	Lset553
	.quad	0
	.quad	0
Ldebug_ranges11:
Lset554 = Ltmp179-Lfunc_begin0
	.quad	Lset554
Lset555 = Ltmp180-Lfunc_begin0
	.quad	Lset555
Lset556 = Ltmp182-Lfunc_begin0
	.quad	Lset556
Lset557 = Ltmp188-Lfunc_begin0
	.quad	Lset557
Lset558 = Ltmp189-Lfunc_begin0
	.quad	Lset558
Lset559 = Ltmp191-Lfunc_begin0
	.quad	Lset559
	.quad	0
	.quad	0
Ldebug_ranges12:
Lset560 = Ltmp195-Lfunc_begin0
	.quad	Lset560
Lset561 = Ltmp198-Lfunc_begin0
	.quad	Lset561
Lset562 = Ltmp200-Lfunc_begin0
	.quad	Lset562
Lset563 = Ltmp204-Lfunc_begin0
	.quad	Lset563
Lset564 = Ltmp258-Lfunc_begin0
	.quad	Lset564
Lset565 = Ltmp260-Lfunc_begin0
	.quad	Lset565
	.quad	0
	.quad	0
Ldebug_ranges13:
Lset566 = Ltmp198-Lfunc_begin0
	.quad	Lset566
Lset567 = Ltmp199-Lfunc_begin0
	.quad	Lset567
Lset568 = Ltmp206-Lfunc_begin0
	.quad	Lset568
Lset569 = Ltmp211-Lfunc_begin0
	.quad	Lset569
Lset570 = Ltmp248-Lfunc_begin0
	.quad	Lset570
Lset571 = Ltmp249-Lfunc_begin0
	.quad	Lset571
	.quad	0
	.quad	0
Ldebug_ranges14:
Lset572 = Ltmp230-Lfunc_begin0
	.quad	Lset572
Lset573 = Ltmp232-Lfunc_begin0
	.quad	Lset573
Lset574 = Ltmp233-Lfunc_begin0
	.quad	Lset574
Lset575 = Ltmp237-Lfunc_begin0
	.quad	Lset575
	.quad	0
	.quad	0
Ldebug_ranges15:
Lset576 = Ltmp230-Lfunc_begin0
	.quad	Lset576
Lset577 = Ltmp232-Lfunc_begin0
	.quad	Lset577
Lset578 = Ltmp233-Lfunc_begin0
	.quad	Lset578
Lset579 = Ltmp237-Lfunc_begin0
	.quad	Lset579
	.quad	0
	.quad	0
Ldebug_ranges16:
Lset580 = Ltmp230-Lfunc_begin0
	.quad	Lset580
Lset581 = Ltmp232-Lfunc_begin0
	.quad	Lset581
Lset582 = Ltmp233-Lfunc_begin0
	.quad	Lset582
Lset583 = Ltmp237-Lfunc_begin0
	.quad	Lset583
	.quad	0
	.quad	0
Ldebug_ranges17:
Lset584 = Ltmp226-Lfunc_begin0
	.quad	Lset584
Lset585 = Ltmp232-Lfunc_begin0
	.quad	Lset585
Lset586 = Ltmp233-Lfunc_begin0
	.quad	Lset586
Lset587 = Ltmp237-Lfunc_begin0
	.quad	Lset587
	.quad	0
	.quad	0
Ldebug_ranges18:
Lset588 = Ltmp61-Lfunc_begin0
	.quad	Lset588
Lset589 = Ltmp63-Lfunc_begin0
	.quad	Lset589
Lset590 = Ltmp64-Lfunc_begin0
	.quad	Lset590
Lset591 = Ltmp68-Lfunc_begin0
	.quad	Lset591
	.quad	0
	.quad	0
Ldebug_ranges19:
Lset592 = Ltmp61-Lfunc_begin0
	.quad	Lset592
Lset593 = Ltmp63-Lfunc_begin0
	.quad	Lset593
Lset594 = Ltmp64-Lfunc_begin0
	.quad	Lset594
Lset595 = Ltmp68-Lfunc_begin0
	.quad	Lset595
	.quad	0
	.quad	0
Ldebug_ranges20:
Lset596 = Ltmp61-Lfunc_begin0
	.quad	Lset596
Lset597 = Ltmp63-Lfunc_begin0
	.quad	Lset597
Lset598 = Ltmp64-Lfunc_begin0
	.quad	Lset598
Lset599 = Ltmp68-Lfunc_begin0
	.quad	Lset599
	.quad	0
	.quad	0
Ldebug_ranges21:
Lset600 = Ltmp70-Lfunc_begin0
	.quad	Lset600
Lset601 = Ltmp71-Lfunc_begin0
	.quad	Lset601
Lset602 = Ltmp73-Lfunc_begin0
	.quad	Lset602
Lset603 = Ltmp79-Lfunc_begin0
	.quad	Lset603
	.quad	0
	.quad	0
Ldebug_ranges22:
Lset604 = Ltmp271-Lfunc_begin0
	.quad	Lset604
Lset605 = Ltmp280-Lfunc_begin0
	.quad	Lset605
Lset606 = Ltmp286-Lfunc_begin0
	.quad	Lset606
Lset607 = Ltmp287-Lfunc_begin0
	.quad	Lset607
Lset608 = Ltmp293-Lfunc_begin0
	.quad	Lset608
Lset609 = Ltmp297-Lfunc_begin0
	.quad	Lset609
Lset610 = Ltmp299-Lfunc_begin0
	.quad	Lset610
Lset611 = Ltmp300-Lfunc_begin0
	.quad	Lset611
Lset612 = Ltmp301-Lfunc_begin0
	.quad	Lset612
Lset613 = Ltmp307-Lfunc_begin0
	.quad	Lset613
Lset614 = Ltmp308-Lfunc_begin0
	.quad	Lset614
Lset615 = Ltmp313-Lfunc_begin0
	.quad	Lset615
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
	.long	3261
	.long	0
LNames4:
	.long	745                     ## dump_argv
	.long	1                       ## Num DIEs
	.long	2295
	.long	0
LNames22:
	.long	968                     ## spawn_proc
	.long	1                       ## Num DIEs
	.long	2742
	.long	0
LNames11:
	.long	999                     ## err_syserr
	.long	1                       ## Num DIEs
	.long	2851
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
	.long	2924
	.long	0
LNames0:
	.long	832                     ## StartsWith
	.long	3                       ## Num DIEs
	.long	2601
	.long	2625
	.long	2655
	.long	0
LNames9:
	.long	810                     ## RemoveSpaces
	.long	1                       ## Num DIEs
	.long	2579
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
	.long	2480
	.long	2530
	.long	0
LNames3:
	.long	983                     ## main
	.long	1                       ## Num DIEs
	.long	1486
	.long	0
LNames14:
	.long	937                     ## fork_pipes
	.long	1                       ## Num DIEs
	.long	2685
	.long	0
LNames5:
	.long	1035                    ## err_syswarn
	.long	1                       ## Num DIEs
	.long	3055
	.long	0
LNames1:
	.long	988                     ## sighandler
	.long	1                       ## Num DIEs
	.long	2766
	.long	0
LNames10:
	.long	1072                    ## exec_nth_command
	.long	1                       ## Num DIEs
	.long	3158
	.long	0
LNames15:
	.long	1022                    ## err_vsyswarn
	.long	1                       ## Num DIEs
	.long	2982
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
	.long	3928
	.short	19
	.byte	0
	.long	0
Ltypes14:
	.long	1220                    ## sigaction
	.long	1                       ## Num DIEs
	.long	3389
	.short	19
	.byte	0
	.long	0
Ltypes48:
	.long	1230                    ## __sigaction_u
	.long	1                       ## Num DIEs
	.long	3444
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
	.long	4131
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
	.long	3730
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
	.long	4027
	.short	22
	.byte	0
	.long	0
Ltypes26:
	.long	1272                    ## __siginfo
	.long	1                       ## Num DIEs
	.long	3525
	.short	19
	.byte	0
	.long	0
Ltypes46:
	.long	1825                    ## __va_list_tag
	.long	1                       ## Num DIEs
	.long	4061
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
	.long	3674
	.short	23
	.byte	0
	.long	0
Ltypes30:
	.long	1510                    ## __darwin_size_t
	.long	1                       ## Num DIEs
	.long	3763
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
	.long	3741
	.short	22
	.byte	0
	.long	0
Ltypes44:
	.long	1673                    ## __darwin_suseconds_t
	.long	1                       ## Num DIEs
	.long	3965
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
	.long	3779
	.short	19
	.byte	0
	.long	0
Ltypes39:
	.long	1756                    ## siginfo_t
	.long	1                       ## Num DIEs
	.long	4005
	.short	22
	.byte	0
	.long	0
Ltypes21:
	.long	1807                    ## __builtin_va_list
	.long	1                       ## Num DIEs
	.long	4038
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
	.long	4016
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
	.long	3752
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
	.long	3723
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
