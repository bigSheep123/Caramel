#冒泡排序的实现

bubble_sort:
        addi    sp,sp,-48
        sd      s0,40(sp)
        addi    s0,sp,48
        sd      a0,-40(s0)
        mv      a5,a1
        sw      a5,-44(s0)
        sw      zero,-20(s0)
        j       .L2
.L6:
        sw      zero,-24(s0)
        j       .L3
.L5:
        lw      a5,-24(s0)
        slli    a5,a5,2
        ld      a4,-40(s0)
        add     a5,a4,a5
        lw      a3,0(a5)
        lw      a5,-24(s0)
        addi    a5,a5,1
        slli    a5,a5,2
        ld      a4,-40(s0)
        add     a5,a4,a5
        lw      a5,0(a5)
        mv      a4,a3
        ble     a4,a5,.L4
        lw      a5,-24(s0)
        addi    a5,a5,1
        slli    a5,a5,2
        ld      a4,-40(s0)
        add     a5,a4,a5
        lw      a5,0(a5)
        sw      a5,-28(s0)
        lw      a5,-24(s0)
        slli    a5,a5,2
        ld      a4,-40(s0)
        add     a4,a4,a5
        lw      a5,-24(s0)
        addi    a5,a5,1
        slli    a5,a5,2
        ld      a3,-40(s0)
        add     a5,a3,a5
        lw      a4,0(a4)
        sw      a4,0(a5)
        lw      a5,-24(s0)
        slli    a5,a5,2
        ld      a4,-40(s0)
        add     a5,a4,a5
        lw      a4,-28(s0)
        sw      a4,0(a5)
.L4:
        lw      a5,-24(s0)
        addiw   a5,a5,1
        sw      a5,-24(s0)
.L3:
        lw      a4,-44(s0)
        lw      a5,-20(s0)
        subw    a5,a4,a5
        sext.w  a5,a5
        addiw   a5,a5,-1
        sext.w  a4,a5
        lw      a5,-24(s0)
        sext.w  a5,a5
        blt     a5,a4,.L5
        lw      a5,-20(s0)
        addiw   a5,a5,1
        sw      a5,-20(s0)
.L2:
        lw      a4,-20(s0)
        lw      a5,-44(s0)
        sext.w  a4,a4
        sext.w  a5,a5
        blt     a4,a5,.L6
        nop
        nop
        ld      s0,40(sp)
        addi    sp,sp,48
        jr      ra

