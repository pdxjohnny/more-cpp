I suffered from the most insane problem ever. I was calling a funciton and when
that funciton returned instead of jumping back to the calling function retq
jumps back to the begining of the function itself.

Here we call the function

0x401cc6 <test_lll_basic_remove()+310>  callq  0x402510 <lll_basic::remove(unsigned int)>

Here is the stack at that time

(gdb) x/40x $rsp
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000
0x7fffffffe540: 0x00603b78      0x00000000      0x00000000      0x00000000

We are about to jump into the remove funciton so lets examine that

```
   │0x402511 <lll_basic::remove(unsigned int)+1>    mov    %rsp,%rbp
   │0x402514 <lll_basic::remove(unsigned int)+4>    sub    $0x60,%rsp
   │0x402518 <lll_basic::remove(unsigned int)+8>    mov    %rdi,-0x10(%rbp)
   │0x40251c <lll_basic::remove(unsigned int)+12>   mov    %esi,-0x14(%rbp)
   │0x40251f <lll_basic::remove(unsigned int)+15>   mov    -0x10(%rbp),%rdi
B+ │0x402523 <lll_basic::remove(unsigned int)+19>   mov    %rdi,-0x40(%rbp)
   │0x402527 <lll_basic::remove(unsigned int)+23>   callq  0x4023f0 <lll_basic::head()>
   │0x40252c <lll_basic::remove(unsigned int)+28>   lea    0xb98(%rip),%rdi        # 0x4030cb
   │0x402533 <lll_basic::remove(unsigned int)+35>   lea    0xba8(%rip),%rsi        # 0x4030e2
   │0x40253a <lll_basic::remove(unsigned int)+42>   mov    $0x3e,%edx
   │0x40253f <lll_basic::remove(unsigned int)+47>   mov    (%rax),%rax
   │0x402542 <lll_basic::remove(unsigned int)+50>   mov    %rax,-0x20(%rbp)
   │0x402546 <lll_basic::remove(unsigned int)+54>   mov    -0x20(%rbp),%rcx
   │0x40254a <lll_basic::remove(unsigned int)+58>   mov    $0x0,%al
   │0x40254c <lll_basic::remove(unsigned int)+60>   callq  0x4007b0 <printf@plt>
   │0x402551 <lll_basic::remove(unsigned int)+65>   mov    %eax,-0x2c(%rbp)
   │0x402554 <lll_basic::remove(unsigned int)+68>   mov    -0x2c(%rbp),%eax
   │0x402557 <lll_basic::remove(unsigned int)+71>   mov    %eax,-0x28(%rbp)
   │0x40255a <lll_basic::remove(unsigned int)+74>   mov    -0x28(%rbp),%eax
   │0x40255d <lll_basic::remove(unsigned int)+77>   mov    %eax,-0x24(%rbp)
   │0x402560 <lll_basic::remove(unsigned int)+80>   cmpq   $0x0,-0x20(%rbp)
   │0x402565 <lll_basic::remove(unsigned int)+85>   jne    0x402574 <lll_basic::remove(unsigned int)+100>
   │0x40256b <lll_basic::remove(unsigned int)+91>   movb   $0x0,-0x1(%rbp)
   │0x40256f <lll_basic::remove(unsigned int)+95>   jmpq   0x4025fc <lll_basic::remove(unsigned int)+236>
   │0x402574 <lll_basic::remove(unsigned int)+100>  cmpl   $0x0,-0x14(%rbp)
   │0x402578 <lll_basic::remove(unsigned int)+104>  jne    0x4025e4 <lll_basic::remove(unsigned int)+212>
   │0x40257e <lll_basic::remove(unsigned int)+110>  mov    -0x20(%rbp),%rax
   │0x402582 <lll_basic::remove(unsigned int)+114>  mov    (%rax),%rcx
   │0x402585 <lll_basic::remove(unsigned int)+117>  mov    0x38(%rcx),%rcx
   │0x402589 <lll_basic::remove(unsigned int)+121>  mov    -0x40(%rbp),%rdi
   │0x40258d <lll_basic::remove(unsigned int)+125>  mov    %rax,-0x48(%rbp)
   │0x402591 <lll_basic::remove(unsigned int)+129>  mov    %rcx,-0x50(%rbp)
   │0x402595 <lll_basic::remove(unsigned int)+133>  callq  0x4023f0 <lll_basic::head()>
   │0x40259a <lll_basic::remove(unsigned int)+138>  mov    -0x48(%rbp),%rdi
   │0x40259e <lll_basic::remove(unsigned int)+142>  mov    %rax,%rsi
   │0x4025a1 <lll_basic::remove(unsigned int)+145>  mov    -0x50(%rbp),%rax
   │0x4025a5 <lll_basic::remove(unsigned int)+149>  callq  *%rax
   │0x4025a7 <lll_basic::remove(unsigned int)+151>  lea    0xb46(%rip),%rdi        # 0x4030f4
   │0x4025ae <lll_basic::remove(unsigned int)+158>  lea    0xb2d(%rip),%rsi        # 0x4030e2
   │0x4025b5 <lll_basic::remove(unsigned int)+165>  mov    $0x46,%edx
   │0x4025ba <lll_basic::remove(unsigned int)+170>  lea    0xb52(%rip),%rcx        # 0x403113
   │0x4025c1 <lll_basic::remove(unsigned int)+177>  mov    %rax,-0x58(%rbp)
   │0x4025c5 <lll_basic::remove(unsigned int)+181>  mov    $0x0,%al
   │0x4025c7 <lll_basic::remove(unsigned int)+183>  callq  0x4007b0 <printf@plt>
   │0x4025cc <lll_basic::remove(unsigned int)+188>  mov    %eax,-0x38(%rbp)
   │0x4025cf <lll_basic::remove(unsigned int)+191>  mov    -0x38(%rbp),%eax
   │0x4025d2 <lll_basic::remove(unsigned int)+194>  mov    %eax,-0x34(%rbp)
   │0x4025d5 <lll_basic::remove(unsigned int)+197>  mov    -0x34(%rbp),%eax
   │0x4025d8 <lll_basic::remove(unsigned int)+200>  mov    %eax,-0x30(%rbp)
   │0x4025db <lll_basic::remove(unsigned int)+203>  movb   $0x1,-0x1(%rbp)
  >│0x4025df <lll_basic::remove(unsigned int)+207>  jmpq   0x4025fc <lll_basic::remove(unsigned int)+236>
   │0x4025e4 <lll_basic::remove(unsigned int)+212>  mov    -0x20(%rbp),%rax
   │0x4025e8 <lll_basic::remove(unsigned int)+216>  mov    (%rax),%rcx
   │0x4025eb <lll_basic::remove(unsigned int)+219>  mov    0x28(%rcx),%rcx
   │0x4025ef <lll_basic::remove(unsigned int)+223>  mov    -0x14(%rbp),%esi
   │0x4025f2 <lll_basic::remove(unsigned int)+226>  mov    %rax,%rdi
   │0x4025f5 <lll_basic::remove(unsigned int)+229>  callq  *%rcx
   │0x4025f7 <lll_basic::remove(unsigned int)+231>  and    $0x1,%al
   │0x4025f9 <lll_basic::remove(unsigned int)+233>  mov    %al,-0x1(%rbp)
   │0x4025fc <lll_basic::remove(unsigned int)+236>  mov    -0x1(%rbp),%al
   │0x4025ff <lll_basic::remove(unsigned int)+239>  and    $0x1,%al
   │0x402601 <lll_basic::remove(unsigned int)+241>  movzbl %al,%eax
   │0x402604 <lll_basic::remove(unsigned int)+244>  add    $0x60,%rsp
   │0x402608 <lll_basic::remove(unsigned int)+248>  pop    %rbp
   │0x402609 <lll_basic::remove(unsigned int)+249>  retq
```

At the callq

0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000
0x7fffffffe540: 0x00603b78      0x00000000      0x00000000      0x00000000

Right after the callq

0x7fffffffe4a8: **0x00401ccb**      0x00000000      0xffffe540      0x00007fff
0x7fffffffe4b8: 0x00402ef2      0x00000000      0xf7538760      0x00007fff
0x7fffffffe4c8: 0x7fffffbb      0x00000000      0x00000037      0x005d6d30
0x7fffffffe4d8: 0x00000058      0x00000000      0xffffe560      0x00007fff
0x7fffffffe4e8: 0x00401b5d      0x00000000      0xffffe550      0x00007fff
0x7fffffffe4f8: 0xffffe540      0x00007fff      0x00616150      0x00000000
0x7fffffffe508: 0xffffe550      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe518: 0x00000037      0x00000037      0x00000037      0x00000001
0x7fffffffe528: 0x00402ae0      0x00000001      0xf7de87b0      0x00007fff
0x7fffffffe538: 0x00000000      0x00000000      0x00603b78      0x00000000

Ok **0x00401ccb** is the correct address to jump back to. It is right after the
callq which was at 0x401cc6

here is at

0x402514 <lll_basic::remove(unsigned int)+4>    sub    $0x60,%rsp

(gdb) x/40x $rsp
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000

After

(gdb) x/40x $rsp
0x7fffffffe440: 0xffffe470      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe450: 0xffffe540      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe460: 0xffffe4a0      0x00007fff      0x004023b3      0x00000000
0x7fffffffe470: 0x00000000      0x00000000      0x00000000      0x01000000
0x7fffffffe480: 0x00402410      0x00000000      0xffffe540      0x00007fff
0x7fffffffe490: 0xffffe540      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000

(gdb) x/40x $rbp
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000

Right before we grab head

(gdb) x/40x $rsp
0x7fffffffe440: 0xffffe470      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe450: 0xffffe540      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe460: 0xffffe4a0      0x00007fff      0x004023b3      0x00000000
0x7fffffffe470: 0x00000000      0x00000000      0x00000000      0x01000000
0x7fffffffe480: 0x00402410      0x00000000      0xffffe540      0x00000000
0x7fffffffe490: 0xffffe540      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000

Here is the stack at this point

64          if (head_ptr == NULL) {

(gdb) x/40x $rsp
0x7fffffffe440: 0xffffe470      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe450: 0xffffe540      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe460: 0xffffe540      0x00007fff      0x004023b3      0x00000000
0x7fffffffe470: 0x00000000      0x0000002b      0x0000002b      0x0000002b
0x7fffffffe480: 0x00616150      0x00000000      0xffffe540      0x00000000
0x7fffffffe490: 0xffffe540      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000

Now we are comparing index to see if it is 0

0x402574 <lll_basic::remove(unsigned int)+100>  cmpl   $0x0,-0x14(%rbp)

(gdb) x/40x $rbp
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000

(gdb) x/40x $rsp
0x7fffffffe440: 0xffffe470      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe450: 0xffffe540      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe460: 0xffffe540      0x00007fff      0x004023b3      0x00000000
0x7fffffffe470: 0x00000000      0x0000002b      0x0000002b      0x0000002b
0x7fffffffe480: 0x00616150      0x00000000      0xffffe540      0x00000000
0x7fffffffe490: 0xffffe540      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000

Sure enough it is zero

(gdb) x/40x $rbp-0x14
0x7fffffffe48c: 0x00000000

Right before jmpq in remove

(gdb) x/40x $rbp
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000
(gdb) x/40x $rsp
0x7fffffffe440: 0xffffe470      0x00007fff      0x00000000      0x00000000
0x7fffffffe450: 0x00402a20      0x00000000      0x00616150      0x00000000
0x7fffffffe460: 0xffffe540      0x00007fff      0x00000039      0x00000039
0x7fffffffe470: 0x00000039      0x0000002b      0x0000002b      0x0000002b
0x7fffffffe480: 0x00616150      0x00000000      0xffffe540      0x00000000
0x7fffffffe490: 0xffffe540      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000

Right at the jmpq

0x4025df <lll_basic::remove(unsigned int)+207>  jmpq   0x4025fc <lll_basic::remove(unsigned int)+236>

(gdb) x/40x $rbp
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000
(gdb) x/40x $rsp
0x7fffffffe440: 0xffffe470      0x00007fff      0x00000000      0x00000000
0x7fffffffe450: 0x00402a20      0x00000000      0x00616150      0x00000000
0x7fffffffe460: 0xffffe540      0x00007fff      0x00000039      0x00000039
0x7fffffffe470: 0x00000039      0x0000002b      0x0000002b      0x0000002b
0x7fffffffe480: 0x00616150      0x00000000      0xffffe540      0x00000000
0x7fffffffe490: 0xffffe540      0x00007fff      0xffffe550      0x01007fff
0x7fffffffe4a0: 0xffffe560      0x00007fff      **0x00401ccb**      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000

And now after

0x4025fc <lll_basic::remove(unsigned int)+236>  mov    -0x1(%rbp),%al

(gdb) x/40x $rsp
0x7fffffffe440: 0xffffe470      0x00007fff      0x00000000      0x00000000
0x7fffffffe450: 0x00402a20      0x00000000      0x00616150      0x00000000
0x7fffffffe460: 0xffffe540      0x00007fff      0x00000039      0x00000039
0x7fffffffe470: 0x00000039      0x0000002b      0x0000002b      0x0000002b
0x7fffffffe480: 0x00616150      0x00000000      0xffffe540      0x00000000
0x7fffffffe490: 0xffffe540      0x00007fff      0xffffe550      0x01007fff
0x7fffffffe4a0: 0xffffe560      0x00007fff      0x00401ccb      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
(gdb) x/40x $rbp
0x7fffffffe4a0: 0xffffe560      0x00007fff      0x00401ccb      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000

Now before we exit the return function we put the stack back

0x402604 <lll_basic::remove(unsigned int)+244>  add    $0x60,%rsp

(gdb) x/40x $rsp
0x7fffffffe440: 0xffffe470      0x00007fff      0x00000000      0x00000000
0x7fffffffe450: 0x00402a20      0x00000000      0x00616150      0x00000000
0x7fffffffe460: 0xffffe540      0x00007fff      0x00000039      0x00000039
0x7fffffffe470: 0x00000039      0x0000002b      0x0000002b      0x0000002b
0x7fffffffe480: 0x00616150      0x00000000      0xffffe540      0x00000000
0x7fffffffe490: 0xffffe540      0x00007fff      0xffffe550      0x01007fff
0x7fffffffe4a0: 0xffffe560      0x00007fff      0x00401ccb      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
(gdb) x/40x $rbp
0x7fffffffe4a0: 0xffffe560      0x00007fff      0x00401ccb      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000

We are now on

0x402608 <lll_basic::remove(unsigned int)+248>  pop    %rbp

right after the add so rbp is back to being rsp

(gdb) x/40x $rbp
0x7fffffffe4a0: 0xffffe560      0x00007fff      0x00401ccb      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000
(gdb) x/40x $rsp
0x7fffffffe4a0: 0xffffe560      0x00007fff      0x00401ccb      0x00000000
0x7fffffffe4b0: 0xffffe540      0x00007fff      0x00402ef2      0x00000000
0x7fffffffe4c0: 0xf7538760      0x00007fff      0x7fffffbb      0x00000000
0x7fffffffe4d0: 0x00000037      0x005d6d30      0x00000058      0x00000000
0x7fffffffe4e0: 0xffffe560      0x00007fff      0x00401b5d      0x00000000
0x7fffffffe4f0: 0xffffe550      0x00007fff      0xffffe540      0x00007fff
0x7fffffffe500: 0x00616150      0x00000000      0xffffe550      0x00007fff
0x7fffffffe510: 0xffffe550      0x00007fff      0x00000037      0x00000037
0x7fffffffe520: 0x00000037      0x00000001      0x00402ae0      0x00000001
0x7fffffffe530: 0xf7de87b0      0x00007fff      0x00000000      0x00000000

Now we are on the retq

0x402609 <lll_basic::remove(unsigned int)+249>  retq

(gdb) x/40x $rsp
0x7fffffffe4a8: 0x00401ccb      0x00000000      0xffffe540      0x00007fff
0x7fffffffe4b8: 0x00402ef2      0x00000000      0xf7538760      0x00007fff
0x7fffffffe4c8: 0x7fffffbb      0x00000000      0x00000037      0x005d6d30
0x7fffffffe4d8: 0x00000058      0x00000000      0xffffe560      0x00007fff
0x7fffffffe4e8: 0x00401b5d      0x00000000      0xffffe550      0x00007fff
0x7fffffffe4f8: 0xffffe540      0x00007fff      0x00616150      0x00000000
0x7fffffffe508: 0xffffe550      0x00007fff      0xffffe550      0x00007fff
0x7fffffffe518: 0x00000037      0x00000037      0x00000037      0x00000001
0x7fffffffe528: 0x00402ae0      0x00000001      0xf7de87b0      0x00007fff
0x7fffffffe538: 0x00000000      0x00000000      0x00603b78      0x00000000
(gdb) x/40x $rbp
0x7fffffffe560: 0xffffe630      0x00007fff      0x004018c8      0x00000000
0x7fffffffe570: 0x00000000      0x00000000      0x00000000      0x00000000
0x7fffffffe580: 0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f      0x2f2f2f2f
0x7fffffffe590: 0x00000000      0x00000000      0x00000000      0x00000000
0x7fffffffe5a0: 0x00000000      0xff000000      0x00000045      0x00000058
0x7fffffffe5b0: 0x00000058      0x00000000      0x00000045      0x00000058
0x7fffffffe5c0: 0x00000058      0xff000000      0x00000045      0x00000058
0x7fffffffe5d0: 0x00000058      0x00000000      0x00000045      0x00000058
0x7fffffffe5e0: 0x00000058      0x000000ff      0x00000045      0x00000058
0x7fffffffe5f0: 0x00000058      0x00000000      0x00000045      0x00000058

Clearly we should be returning to the test function!!!!!!

rsp is 0x00401ccb so retq should take us back!!!!

Alright I have been documenting this as I go. I just realized this was the
problem.

```cpp
   │13      int test_lll_basic_remove() {
B+ │14          lll_basic list;
   │15          MACRO_TEST_CANT_EQ(list.add(), NULL);
   │16          MACRO_LOG_STR("Removing...");
  >│17          MACRO_TEST_CANT_EQ(list.remove(0), true);
   │18          MACRO_LOG_STR("Removed");
   │19          return EXIT_SUCCESS;
   │20      }
```

Here is the can EQ function.

```cpp
#define MACRO_TEST_INT_CANT_EQ(var, should_be) \
({\
    if (var == should_be) {\
        MACRO_TEST_LOG_ERROR(#var " should not have been %d but was %d", should_be, var);\
        return -1;\
    }\
})
```

var was the function call and therefore it called the function twice. Once to
check if it was equal and once to report therefore it was a different value
each time.

This is the offending test case. The problem is that I copy pasted from the add
test case. That should have been:

```cpp
int test_lll_basic_remove() {
    lll_basic list;
    MACRO_TEST_CANT_EQ(list.add(), NULL);
    MACRO_LOG_STR("Removing...");
    bool removed = list.remove(0);
    MACRO_TEST_EQ(removed, true);
    MACRO_LOG_STR("Removed");
    return EXIT_SUCCESS;
}
```

This way it doesnt call the remove function twice which is what lead me to
believe that it was jumping right back into the function but it is really just
doing that so it can print that the test case failed.

I guess the bright side is that I still know how to use gdb and that I now know
some more about x64 assembly, yay.

When I was debugging I used gdb in tui mode. I just discovered this last week
and it was a huge help. It lets you switch bewteen the source and assembly and
shows you what instuction you are on. I found it so much eaiser to work with
than how I had previously used gdb. Last program I mentioned how I prefer
valgrind to gdb. I still do because I think it helps me find more errors but
gdb was great for figuring out what is going on when youre having unexpected
behavior.
I also started using clang rather than gcc. clang gives way better error
messages and best of all comes with a static analysis tool, scan-build. Its
similar to coverity but you can run it localy. Not quite as good but it gets
the job done.
