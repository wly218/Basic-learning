#include "polygon_plugins/polygon_plugins.hpp"
#include <polygon_base/regular_polygon.hpp>
#include <cmath>

namespace polygon_plugins
{

    PolygonPlugins::PolygonPlugins()
    {
    }

    PolygonPlugins::~PolygonPlugins()
    {
    }

}  // namespace polygon_plugins

namespace polygon_plugins
{
    class Square:public polygon_base::RegularPolygon
    {
    public:
        void initialize(double side_length) override
        {
            side_length_ = side_length;
        }
        double area() override
        {
            return side_length_ * side_length_;
        }
    protected:
        double side_length_;
    };

    class Triangle:public polygon_base::RegularPolygon
    {
    public:
        void initialize(double side_length) override
        {
            side_length_ = side_length;
        }
        double getHeight()
        {
            return sqrt((side_length_ * side_length_)-((side_length_ / 2) * (side_length_ / 2)));
        }
        double area() override
        {
            return 0.5 * side_length_ * getHeight();
        }
    protected:
        double side_length_;
    };
}

#include <pluginlib/class_list_macros.hpp>
//与pluginlib相关，调用了一些注册类为实际插件的神奇宏
//参数 插件类的完全限定类型 基类的完全限定类型
PLUGINLIB_EXPORT_CLASS(polygon_plugins::Square,polygon_base::RegularPolygon)
PLUGINLIB_EXPORT_CLASS(polygon_plugins::Triangle,polygon_base::RegularPolygon)
