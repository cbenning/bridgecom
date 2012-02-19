
class System
{
private:
    std::string fileName;
    std::string name;
    std::string backdrop;
    Body* rootBody;
    ISceneManager* smgr;
    IVideoDriver* driver;
    Body* processRoot(xml_document doc);
    Body* processChild(xml_node tmpRoot, Body* parent);

public:
    System(ISceneManager* smgr, IVideoDriver* driver, std::string fileName);
    void buildSystem();

};
