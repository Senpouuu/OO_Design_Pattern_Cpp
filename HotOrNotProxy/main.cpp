#include <iostream>
#include <memory>

// Subject
class PersonBean {
public:
    std::string Name;
    std::string Gender;
    std::string Interests;
    int rating = 0;
    int ratingCount = 0;

    virtual std::string getName() {}
    virtual std::string getGender() {}
    virtual std::string getInterests() {}
    virtual int getHotOrNotRating() {}
    virtual void setName(std::string name) {}
    virtual void setGender(std::string gender) {}
    virtual void setInterests(std::string interests) {}
    virtual void setHotOrNotRating(int rating) {}
};

// Real Subject
class PersonBeanImpl : public PersonBean {
public:
    std::string getName() override {
        return Name;
    }

    std::string getGender() override {
        return Gender;
    }

    std::string getInterests() override {
        return Interests;
    }

    int getHotOrNotRating() override {
        if (ratingCount == 0) return 0;
        return (rating / ratingCount);
    }

    void setName(std::string name) override {
        this->Name = name;
    }

    void setGender(std::string gender) override {
        this->Gender = gender;
    }

    void setInterests(std::string interests) override {
        this->Interests = interests;
    }

    void setHotOrNotRating(int rating) override {
        this->rating += rating;
        ratingCount++;
    }
};

// InvocationHandler interface
class InvocationHandler {
public:
    virtual std::string invoke(std::string methodName, std::shared_ptr<PersonBean> realSubject, std::string arg = "") = 0;
};

// Proxy class
class Proxy : public PersonBean {
private:
    std::shared_ptr<PersonBean> realSubject;
    std::shared_ptr<InvocationHandler> handler;

public:
    Proxy(std::shared_ptr<PersonBean> realSubject, std::shared_ptr<InvocationHandler> handler)
        : realSubject(realSubject), handler(handler) {}

    std::string getName() override {
        return handler->invoke("getName", realSubject);
    }

    std::string getGender() override {
        return handler->invoke("getGender", realSubject);
    }

    std::string getInterests() override {
        return handler->invoke("getInterests", realSubject);
    }

    int getHotOrNotRating() override {
        return std::stoi(handler->invoke("getHotOrNotRating", realSubject));
    }

    void setName(std::string name) override {
        handler->invoke("setName", realSubject, name);
    }

    void setGender(std::string gender) override {
        handler->invoke("setGender", realSubject, gender);
    }

    void setInterests(std::string interests) override {
        handler->invoke("setInterests", realSubject, interests);
    }

    void setHotOrNotRating(int rating) override {
        handler->invoke("setHotOrNotRating", realSubject, std::to_string(rating));
    }
};

// OwnerInvocationHandler class: Allows modifying own info, but not rating oneself
class OwnerInvocationHandler : public InvocationHandler {
public:
    std::string invoke(std::string methodName, std::shared_ptr<PersonBean> realSubject, std::string arg = "") override {
        if (methodName == "getName") {
            return realSubject->getName();
        } else if (methodName == "getGender") {
            return realSubject->getGender();
        } else if (methodName == "getInterests") {
            return realSubject->getInterests();
        } else if (methodName == "getHotOrNotRating") {
            return std::to_string(realSubject->getHotOrNotRating());
        } else if (methodName == "setName") {
            realSubject->setName(arg);
            return "";
        } else if (methodName == "setGender") {
            realSubject->setGender(arg);
            return "";
        } else if (methodName == "setInterests") {
            realSubject->setInterests(arg);
            return "";
        } else if (methodName == "setHotOrNotRating") {
            std::cout << "Cannot rate yourself!" << std::endl;
            return "";
        }
        return "";
    }
};

// NonOwnerInvocationHandler class: Allows rating others, but not modifying their info
class NonOwnerInvocationHandler : public InvocationHandler {
public:
    std::string invoke(std::string methodName, std::shared_ptr<PersonBean> realSubject, std::string arg = "") override {
        if (methodName == "getName") {
            return realSubject->getName();
        } else if (methodName == "getGender") {
            return realSubject->getGender();
        } else if (methodName == "getInterests") {
            return realSubject->getInterests();
        } else if (methodName == "getHotOrNotRating") {
            return std::to_string(realSubject->getHotOrNotRating());
        } else if (methodName == "setName" || methodName == "setGender" || methodName == "setInterests") {
            std::cout << "Cannot modify others' information!" << std::endl;
            return "";
        } else if (methodName == "setHotOrNotRating") {
            realSubject->setHotOrNotRating(std::stoi(arg));
            return "";
        }
        return "";
    }
};

// AdminInvocationHandler class: Allows modifying any info including rating
class AdminInvocationHandler: public InvocationHandler {
public:
    std::string invoke(std::string methodName, std::shared_ptr<PersonBean> realSubject, std::string arg = "") override {
        if (methodName == "getName") {
            return realSubject->getName();
        } else if (methodName == "getGender") {
            return realSubject->getGender();
        } else if (methodName == "getInterests") {
            return realSubject->getInterests();
        } else if (methodName == "getHotOrNotRating") {
            return std::to_string(realSubject->getHotOrNotRating());
        } else if (methodName == "setName") {
            realSubject->setName(arg);
            return "";
        } else if (methodName == "setGender") {
            realSubject->setGender(arg);
            return "";
        } else if (methodName == "setInterests") {
            realSubject->setInterests(arg);
            return "";
        } else if (methodName == "setHotOrNotRating") {
            realSubject->setHotOrNotRating(std::stoi(arg));
            return "";
        }
        return "";
    }
};

int main() {
    std::shared_ptr<PersonBean> person = std::make_shared<PersonBeanImpl>();
    std::shared_ptr<InvocationHandler> ownerHandler = std::make_shared<OwnerInvocationHandler>();
    std::shared_ptr<InvocationHandler> nonOwnerHandler = std::make_shared<NonOwnerInvocationHandler>();
    std::shared_ptr<InvocationHandler> adminHandler = std::make_shared<AdminInvocationHandler>();

    // Proxy for own data
    Proxy ownerProxy(person, ownerHandler);
    ownerProxy.setName("John Doe");
    ownerProxy.setGender("Male");
    ownerProxy.setInterests("Programming, Chess");

    std::cout << "Name: " << ownerProxy.getName() << std::endl;
    std::cout << "Gender: " << ownerProxy.getGender() << std::endl;
    std::cout << "Interests: " << ownerProxy.getInterests() << std::endl;
    ownerProxy.setHotOrNotRating(5);  // This should be blocked by the handler

    // Proxy for rating others
    Proxy nonOwnerProxy(person, nonOwnerHandler);
    nonOwnerProxy.setHotOrNotRating(5);  // This should be allowed
    std::cout << "Rating: " << nonOwnerProxy.getHotOrNotRating() << std::endl;
    nonOwnerProxy.setName("Jane Doe");  // This should be blocked by the handler

    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

    // Admin Proxy
    Proxy adminProxy(person, adminHandler);
    adminProxy.setHotOrNotRating(1000);  // This should be allowed

    std::cout << "Name: " << adminProxy.getName() << std::endl;
    std::cout << "Gender: " << adminProxy.getGender() << std::endl;
    std::cout << "Interests: " << adminProxy.getInterests() << std::endl;
    std::cout << "Rating: " << adminProxy.getHotOrNotRating() << std::endl;

    return 0;
}
