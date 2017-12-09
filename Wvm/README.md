# Wvm
a simple virtual machine , server the compiler Woo

# Use
The program received a intermediate language file :
![img](https://github.com/TanSilver/Wvm/blob/master/da.png)

the content of asm.txt:
```
FUNCTION fibonacci
t0 = s: fibonacci sequence \n
t1 = t0
PARAM t1
t2 = CALL print 1
t5 = d: 0
i = t5
t8 = d: 1
j = t8
t10 = d: 1
k = t10
LABEL 1
t12 = i
t13 = d: 10
IF t12 < t13 GOTO LABEL 2
t14 = s:  
t15 = s:  
t16 = j
PARAM t16
t17 = t14
PARAM t17
t18 = k
PARAM t18
t19 = t15
PARAM t19
t20 = CALL print 4
t21 = j
t22 = k
t23 + t21 t22
t24 = t23
j = t24
t25 = k
t26 = j
t27 + t25 t26
t28 = t27
k = t28
t29 = i
t30 = d: 1
t31 + t29 t30
t32 = t31
i = t32
GOTO LABEL 1
LABEL 2
t33 = s: \n
t34 = t33
PARAM t34
t35 = CALL print 1
EXIST
t36 = CALL fibonacci 0
  ```
# Support Instruction
IMOV,IJMP,ISTR,ILDR,ICMP,IADD,ISUB,IMUL,IDIV,IOUT
