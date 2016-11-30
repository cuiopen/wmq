#include <stdlib.h>
#include <assert.h>
#include "server_dispatch.h"

#include "msg_queue.h"
#include "topic_fd_map.h"
#include "mq_sender.h"
#include "message.h"

/**
 * 根据消息队列的负载，选在消息队列
 */
static
int select_message_qeueue(server_t *master_server){
	int i;
	int min_len=100000000;
	int queue_no=0;
	
	for(i=0;i<master_server->queue_count;i++){
		int count=count_queue(master_server->mq[i]->list_queue);
		if(count<=min_len){
			queue_no=i;
			min_len=count;
		}
	}
	return queue_no;
}

/**
 * 反序列化消息体，根据编码模式反序列化消息体
 * @param pkg [description]
 * 
 */
static message_t* deserialize_message(socket_pkg_t *pkg){
	message_t* msg=NULL;
	assert(pkg != NULL);

	switch(pkg->code){
		case CODE_NATIVE:{
			msg=(message_t *)pkg->msg; //转化为结构体
			break;
		}
		case CODE_JSON:{
			break;
		}
		case CODE_GZIP:{
			break;
		}
		case CODE_PROTOBUF:{
			break;
		}
		default:break;
	}

	return msg;
}

/**
 * 处理消息包,根据处理操作
 * @param mq  [发送的消息队列通道]
 * @param pkg [消息包]
 */
static void dispatch_service(server_t *master_server,socket_pkg_t *pkg){
	switch(pkg->cmd){
		case MQ_OPEN:{

			break;
		}
		case MQ_CLOSE:{
			break;
		}
		case MQ_SUBTOPIC:{    // 注册topic
			add_topic(master_server->ht,pkg->topic,pkg->fd);
			break;
		}
		case MQ_PUBMSG:{	//发送消息到消息队列
			int idx=select_message_qeueue(master_server);
			msg_queue_t *mq=master_server->mq[idx]; //选择负载最小的队列
			message_t *msg=deserialize_message(pkg);
			send_msg_mq(mq,msg);
			break;
		}
		default:
			break;
	}
}

void handle_socket_pkg(server_t *master_server,socket_pkg_t *pkg)
{
	dispatch_service(master_server,pkg);	
}

