GLOBAL _syscallHandler
EXTERN syscallDraw
EXTERN syscallRead

_syscallHandler:
    cmp rax, 1
    je _draw

    cmp rax, 2
    je _read

    iretq

_draw:
    call syscallDraw
    iretq

_read:
    call syscallRead
    iretq