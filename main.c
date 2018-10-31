/*File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 *2017-12-15      DQL          the first version 
 */

#include "app_uSart.h"
#include "pin_def.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

struct rt_thread 		*led1_thread;
struct rt_thread 		usart_test1_thread;
void test_thread_entry(void* parameter)
{    
    rt_uint8_t ch[10];
		rt_uint8_t a=0,b=0;
		rt_uint8_t i=0;
    //uart_open("uart3") 
    /* 打开串口 */
    if (uart_open("uart3") != RT_EOK)
    {
        rt_kprintf("uart open error.\n");
       
    }
       
    /* 单个字符写 */
    uart_putchar('2');
    uart_putchar('0');
    uart_putchar('1');
    uart_putchar('8');
    uart_putchar('\n');
    /* 写字符串 */
    uart_putstring("Hello RT-Thread!\r\n");
    
    while (1)
    {   
			for(i=0;i<13;i++)
			{
					ch[i]=uart_getchar();
				
					if(ch[0]!=0x02)
					{
						i=0;
					}
					rt_thread_delay(5);
			}
			
				if(ch[1]==0x05)
				{
					
					rt_pin_write(PB1,a);
					a=~a;
					ch[1]=0;
				}
				
    }       
	}			


void usart_test1_entry(void *parameter)
{
	
	rt_uint8_t tick_count;
	
	while(1)
	{
		
		tick_count=rt_tick_get();
//		rt_kprintf("ticknumber=%d\n",tick_count);
	
		rt_thread_delay(1);
	
	}
}
int main(void)
{
    
    rt_thread_t tid;
		rt_thread_t tid1;
       
    /* 创建test线程 */
    tid = rt_thread_create("test",
                    test_thread_entry, 
                    RT_NULL,
                    1024, 
										2, 
                    10);
	
		tid1=rt_thread_create("test2",
													usart_test1_entry,
													RT_NULL,
													512,
													3,
													10);
    /* 创建成功则启动线程 */
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    if (tid1!= RT_NULL)
        rt_thread_startup(tid1);    
    return 0;
}
