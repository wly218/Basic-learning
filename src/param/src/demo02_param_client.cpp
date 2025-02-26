#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class MyParamClient : public rclcpp::Node
{
public:
    MyParamClient():Node("ParamDemoClient_node")
    {
        paramClient = std::make_shared<rclcpp::SyncParametersClient>(this,"my_param");
    }
    bool connect_server()
    {
        while(!paramClient->wait_for_service(1s))
        {
            if(!rclcpp::ok())
            {
                return false;
            }
            RCLCPP_INFO(this->get_logger(),"服务未连接...");
        }
        return true;
    }

    //查询参数
    void get_param()
    {
        RCLCPP_INFO(this->get_logger(),"-------------参数客户端查询参数------------");
        double height = paramClient->get_parameter<double>("height");
        RCLCPP_INFO(this->get_logger(),"height = %.2f",height);
        RCLCPP_INFO(this->get_logger(),"car_type存在?%d",paramClient->has_parameter("car_type"));
        auto params = paramClient->get_parameters({"car_type","height","wheels"});
        for(auto &param:params)
        {   
            RCLCPP_INFO(this->get_logger(),"%s = %s",param.get_name().c_str(),param.value_to_string().c_str());
        }
    }
    //修改参数
    void update_param()
    {
        RCLCPP_INFO(this->get_logger(),"-------------参数客户端修改参数------------");
        paramClient->set_parameters({rclcpp::Parameter("car_type","Mouse"),
                                    rclcpp::Parameter("height",2.0),
                                    rclcpp::Parameter("width",0.15),
                                    rclcpp::Parameter("wheels",6)});
    }
private:
    rclcpp::SyncParametersClient::SharedPtr paramClient;
};

int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    auto paramClient = std::make_shared<MyParamClient>();
    bool flag = paramClient->connect_server();
    if(!flag)
    {
        return 0;
    }
    paramClient->get_param();
    paramClient->update_param();
    paramClient->get_param();

    rclcpp::shutdown();
    return 0;
}