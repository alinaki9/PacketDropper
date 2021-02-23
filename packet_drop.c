/* packet_drop.c
 * Author: Ali Naki
 * Updated: 24-Feb-2021
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>  
#include <linux/tcp.h>
#include <linux/ip.h>
#include <linux/icmp.h>

static struct nf_hook_ops nfho_pre_routing;

unsigned int pre_routing_hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct iphdr *ip_header = (struct iphdr *)skb_network_header(skb);
	struct tcphdr *tcp_header;
	
	if (!skb)
	{			
		return NF_ACCEPT;
	}

	if (ip_header->protocol == IPPROTO_TCP)
	{
		tcp_header = (struct tcphdr *)skb_transport_header(skb);
		if ((tcp_header->syn) && (!tcp_header->ack && !tcp_header->urg && !tcp_header->rst 
		&& !tcp_header->fin && !tcp_header->psh))
		{
			printk(KERN_INFO "SYN Scan Detected! \n");
		}

		else if ((tcp_header->fin) && (!tcp_header->ack && !tcp_header->urg && !tcp_header->rst 
		&& !tcp_header->syn && !tcp_header->psh))
		{
			printk(KERN_INFO "FIN Scan Detected! \n");
		}

		else if (!tcp_header->syn && !tcp_header->ack && !tcp_header->urg && !tcp_header->rst 
		&& !tcp_header->fin && !tcp_header->psh)
		{
			printk(KERN_INFO "NULL Scan Detected! \n");
		}
	}
	
	return NF_DROP;
	
}


static int hello_init(void)
{

	nfho_pre_routing.hook = pre_routing_hook_func;
	nfho_pre_routing.hooknum = NF_INET_PRE_ROUTING;
	nfho_pre_routing.pf = PF_INET;
	nfho_pre_routing.priority = NF_IP_PRI_FIRST;
	nf_register_net_hook(&init_net, &nfho_pre_routing);

	return 0;
}

static void hello_exit(void)
{ 
	nf_unregister_net_hook(&init_net, &nfho_pre_routing); 
}

module_init(hello_init);
module_exit(hello_exit);
