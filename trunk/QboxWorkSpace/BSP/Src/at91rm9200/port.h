#ifndef __VXPORT_H__
#define __VXPORT_H__


#ifndef __ASSEMBLER__
#define spin_lock_irq(x)
#define spin_unlock_irq(x)
#define spin_lock_init(x) *x=0
#define request_irq(id, fn, x, name, dev)  intConnect(INUM_TO_IVEC(id), (VOIDFUNCPTR)fn, (int)dev)
    
#define free_irq(id, dev) {intDisable(id); intConnect(INUM_TO_IVEC(id),0,(int)dev);}
#define spin_lock_irqsave(x,y) 
#define spin_unlock_irqrestore(x,y) 
typedef  unsigned long spinlock_t; 
#define KERN_ERR
#define KERN_INFO
static __inline void printk(const char* x,...)
{
	
	
}
static __inline void DEBUG(int x,...)
{
	
	
}

static __inline void udelay(long l)
{
int i;
	for( i=0;i<l*1000;i++);
}

#define DEBUG_LOG(x,fmt, p1, p2, p3, p4, p5, p6) \
        logMsg(fmt, (int)(UINT32)(p1), (int)(UINT32)(p2), (int)(UINT32)(p3), (int)(UINT32)(p4), (int)(UINT32)(p5), (int)(UINT32)(p6))


#endif
#endif
