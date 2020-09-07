#include <Application.h>
#include <memory>

int main(int argc, char **argv)
{
    std::shared_ptr<Application> app = std::make_shared<Application>();

    return app->run(argc, argv);
}