 void wsdup(void);
 void wsdcl(void);
 void sendpcdata(void);
 // ... 原有代码 ...
void sendpcdata(void);

// [新增] 远程控制模式变量声明
// 0: 自动模式 (默认)
// 1: 远程强制开启
// 2: 远程强制关闭
extern unsigned char remote_ctrl_mode;