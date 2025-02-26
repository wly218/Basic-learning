#include "rclcpp/rclcpp.hpp"

class MyParam:public rclcpp::Node
{
public:
    //为什么这里的 NodeOptions 这么奇怪？？？
    MyParam():Node("my_param",rclcpp::NodeOptions().allow_undeclared_parameters(true)){}
    //声明参数并设置默认值
    void declare_param()
    {
       this->declare_parameter("car_type","Cadillac");
       this->declare_parameter("height",1.50);
       this->declare_parameter("wheels",4);
       this->set_parameter(rclcpp::Parameter("other","Wang"));
    }
    //查询参数
    void get_param()
    {
      //获取指定的参数
      RCLCPP_INFO(this->get_logger(),"----------查询参数----------");
      rclcpp::Parameter car_type = this->get_parameter("car_type");
      RCLCPP_INFO(this->get_logger(),"car_type:%s",car_type.as_string().c_str());
      rclcpp::Parameter height = this->get_parameter("height");
      RCLCPP_INFO(this->get_logger(),"height:%.2f",height.as_double());
      rclcpp::Parameter wheels = this->get_parameter("wheels");
      RCLCPP_INFO(this->get_logger(),"wheels:%ld",wheels.as_int());

      //判断包含
      RCLCPP_INFO(this->get_logger(),"包含car_type? %d",this->has_parameter("car_type"));
      RCLCPP_INFO(this->get_logger(),"包含car_weight? %d",this->has_parameter("car_weight"));

      //获取所有
      auto params = this->get_parameters({"car_type","height","wheels"});
      for(auto &param : params)
      {
          RCLCPP_INFO(this->get_logger(),"name = %s,value = %s",param.get_name().c_str(),param.value_to_string().c_str());
      }
    }

    //修改参数
    void update_param()
    {
        RCLCPP_INFO(this->get_logger(),"----------修改参数----------");
        this->set_parameter(rclcpp::Parameter("height",1.75));
        RCLCPP_INFO(this->get_logger(),"height:%.2f",this->get_parameter("height").as_double());
    }

    //删除参数
    void del_param()
    {
        RCLCPP_INFO(this->get_logger(),"----------删除参数----------");
        //只能删除未被声明的参数
        RCLCPP_INFO(this->get_logger(),"删除操作前,other存在吗?%d",this->has_parameter("other"));
        this->undeclare_parameter("other");
        RCLCPP_INFO(this->get_logger(),"删除操作后,other存在吗?%d",this->has_parameter("other"));
    }
private:

};

int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    auto paramServer = std::make_shared<MyParam>();
    paramServer->declare_param();
    paramServer->get_param();
    paramServer->update_param();
    paramServer->del_param();
    rclcpp::spin(paramServer);
    rclcpp::shutdown();
    return 0;
}
