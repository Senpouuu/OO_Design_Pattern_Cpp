#include <iostream>
#include <thread>
#include <chrono>

class Icon{
public:
    virtual int getIconWidth(){};
    virtual int getIconHeight(){};
    virtual int paintIcon(){};
};

class ImageIcon :public Icon{
public:
    std::string imgURL;
    ImageIcon(std::string URL):imgURL(URL)
    {
        std::cout<<"URL is " << imgURL << std::endl;
    }

    int getIconHeight() override{
        return 1600;
    }

    int getIconWidth() override{
        return 1600;
    }

    int paintIcon() override{
        std::cout<<"Here is your Image!\r\n";
        std::cout<<"Here is your Image!\r\n";
        std::cout<<"Here is your Image!\r\n";
        std::cout<<"Here is your Image!\r\n";
        std::cout<<"Here is your Image!\r\n";
        std::cout<<"Here is your Image!\r\n";
        return 0;
    }

};


class ImageProxy:public Icon{
public:
    ImageIcon* imgIcon = nullptr;
    std::string imgURL;
    bool retrieving = false;

    ImageProxy(std::string URL):imgURL(URL){};

    int getIconHeight() override{
        if(imgIcon!= nullptr)
            return imgIcon->getIconHeight();
        else
            return 800;
    }

    int getIconWidth() override{
        if(imgIcon!= nullptr)
            return imgIcon->getIconHeight();
        else
            return 800;
    }

    int paintIcon() override{
        if(imgIcon!= nullptr)
            imgIcon->paintIcon();
        else
        {
            std::cout<<"loading......";
            //std::this_thread::sleep_for(std::chrono::seconds(3));
            if(!retrieving)
            {
                retrieving = true;
                imgIcon = new ImageIcon(imgURL);
                this->paintIcon();
            }
        }
        return 0;
    }
};


int main() {

    auto porxy = new ImageProxy("baidu.com");
    std::cout << porxy->getIconHeight() << std::endl;
    std::cout << porxy->getIconWidth() << std::endl;
    porxy->paintIcon();
    std::cout << "#################################" << std::endl;
    std::cout << porxy->getIconHeight() << std::endl;
    std::cout << porxy->getIconWidth() << std::endl;
    porxy->paintIcon();
    return 0;
}
