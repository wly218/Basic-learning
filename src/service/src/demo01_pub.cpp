#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/addint.hpp"
//简化写法
using base_interfaces_demo::srv::Addint;
//使用占位符
//也可以不用命名空间，指定使用的占位符，如_1,_2等等
using namespace std::placeholders;

class MyServicePub:public rclcpp::Node
{
public:
    //构造函数
    MyServicePub():Node("service_pub")
    {
        //似乎也可以直接传入函数的地址
        server_ = this->create_service<Addint>("service",std::bind(&MyServicePub::add,this,_1,_2));
        RCLCPP_INFO(this->get_logger(),"服务端启动");
    }
private:
    //服务端指针
    rclcpp::Service<Addint>::SharedPtr server_;
    //服务绑定的函数，在本例中实现两个数的加法
    void add(const Addint::Request::SharedPtr req,Addint::Response::SharedPtr res)
    {
        res->num = req->num1 + req->num2;
        RCLCPP_INFO(this->get_logger(),"结果为：%d",res->num);
    }
};

int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<MyServicePub>());
    rclcpp::shutdown();
    return 0;
}