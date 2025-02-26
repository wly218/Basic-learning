#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"

using base_interfaces_demo::msg::Student;
//占位符
using std::placeholders::_1;

class MySub:public rclcpp::Node
{
public:
    MySub():Node("topic_subscriber")
    {
        //创建订阅方，订阅“my_topic”话题发布的消息，消息队列长度为10，然后绑定回调函数处理订阅到的消息
        subscription_ = this->create_subscription<Student>("my_topic",10,std::bind(&MySub::topic_callback,this,_1));
    }
private:
    void topic_callback(const Student& stu) const
    {
        RCLCPP_INFO(this->get_logger(),"订阅到的学生信息为：姓名：%s,年龄：%d,身高：%.2f",stu.name.c_str(),stu.age,stu.height);
    }
    rclcpp::Subscription<Student>::SharedPtr subscription_;
};

int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<MySub>());
    rclcpp::shutdown();
    return 0;
}