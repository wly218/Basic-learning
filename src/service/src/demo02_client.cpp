#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/addint.hpp"

using base_interfaces_demo::srv::Addint;
using namespace std::chrono_literals;

class MyServiceSub:public rclcpp::Node
{
public:
    MyServiceSub():Node("service_sub")
    {
        client_ = this->create_client<Addint>("service");
        RCLCPP_INFO(this->get_logger(),"客户端创建..");
    }
    bool connect_server()
    {
        while(!client_->wait_for_service(2s))
        {
            if(!rclcpp::ok())
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"强制退出！");
                return false;
            }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"正在连接中");
        }
        return true;
    }
    rclcpp::Client<Addint>::FutureAndRequestId send_request(int32_t num1,int32_t num2)
    {
        auto request = std::make_shared<Addint::Request>();
        request->num1 = num1;
        request->num2 = num2;
        //真正发送请求并且返回一个状态
        return client_->async_send_request(request);
    }
private:
    rclcpp::Client<Addint>::SharedPtr client_;
};

int main(int argc,char** argv)
{
    //虽然但是为什么argc要多一个
    if(argc!=3)
    {
        //不在节点中时，用rclcpp::get_logger
        RCLCPP_WARN(rclcpp::get_logger("rclcpp"),"请输入正确的数据！");
        return 1;
    }
    //初始化客户端
    rclcpp::init(argc,argv);
    auto client = std::make_shared<MyServiceSub>();
    //标志是否成功建立连接
    auto flag = client->connect_server();
    if(!flag)
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"服务连接失败..");
        return 0;
    }
    //把参数转换成int
    auto response = client->send_request(atoi(argv[1]),atoi(argv[2]));
    if(rclcpp::spin_until_future_complete(client,response)==rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(client->get_logger(),"请求处理正常..");
        RCLCPP_INFO(client->get_logger(),"响应结果：%d",response.get()->num);
    }
    else
    {
        RCLCPP_INFO(client->get_logger(),"请求异常");
    }
    rclcpp::shutdown();
    return 0;
}