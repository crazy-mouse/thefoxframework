#ifndef _THEFOX_RPC_RPCSERVER_H_
#define _THEFOX_RPC_RPCSERVER_H_

#include <base/Types.h>
#include <net/TcpServer.h>
#include <net/rpc/common.h>
#include <net/rpc/rpc.pb.h>
#include <google/protobuf/service.h>

namespace thefox
{

class RpcServiceImpl;

class RpcServer
{
public:
	RpcServer(EventLoop *loop);
	~RpcServer();

	void registerService(gpb::Service *service);
	bool start(const InetAddress &listen);
	void sendOnewayMessage(const ConnectionPtr &conn, const gpb::Message *message);
	void setHearthBeathCallback(const HeartBeathCallback &cb);

private:
	THEFOX_DISALLOW_EVIL_CONSTRUCTORS(RpcServer);
	void onConnection(const ConnectionPtr &conn);
	void onClose(const ConnectionPtr &conn);
	void onMessage(const ConnectionPtr &conn, Buffer *buf, const Timestamp recvTime);

	// 服务端：处理请求
	void handleCallMessage(const ConnectionPtr &conn, const rpc::Call &call, Timestamp recvTime);

	std::shared_ptr<TcpServer> _server;
	ServiceManagerPtr _serviceManager;
	std::unique_ptr<RpcServiceImpl> _rpcServiceImpl;
	TaskManagerPtr _taskManager;
};

} // namespace thefox

#endif  // _THEFOX_RPC_RPCSERVER_H_

