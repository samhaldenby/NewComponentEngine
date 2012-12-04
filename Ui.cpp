#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Ui.h"
#include "Core.h"
#include "Telegram.h"
#include "MessageCentre.h"

Ui::Ui(Core* core, std::string uiConfigFileName) : core_(core)
{
    //read config file
    boost::property_tree::ptree tree;
    read_xml(uiConfigFileName, tree);

    screenSize_ = Vector2d(tree.get<int>("Ui.Dimensions.x"),tree.get<int>("Ui.Dimensions.y"));

    window_ = new sf::RenderWindow(sf::VideoMode(screenSize_.x, screenSize_.y, 32), "Ui");
    window_->SetFramerateLimit(60);

    //hook into event system
    input_ = (const_cast<sf::Input*>(&getWindow()->GetInput()));
}



sf::RenderWindow* Ui::getWindow()
{
    return window_;
}

void Ui::setPlayer(ObjectId id)
{
    playerId_ = id;
}


void Ui::update(double elapsed)
{

  //grab Input events for player
//    const sf::Input& input = core_->getUi()->getWindow()->GetInput();

    sf::Event event;

    //check for close events etc
    while(core_->getUi()->getWindow()->GetEvent(event))
    {
         // Window closed
        if (event.Type == sf::Event::Closed)
            exit(0);

        // Escape key pressed
        if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
            exit(0);
    }


    if(input_->IsMouseButtonDown(sf::Mouse::Left))
    {
        //get coordinates
        double xMouse = input_->GetMouseX();
        double yMouse = input_->GetMouseY();
        std::cout << "Clicked " << xMouse << "," << yMouse << std::endl;

            //set movement
            Parameters moveParameters;
            moveParameters.push_back("move");
            moveParameters.push_back("setLocalDest");
            std::stringstream xSS(""), ySS("");
            xSS << xMouse;
            ySS << yMouse;
            moveParameters.push_back(xSS.str());
            moveParameters.push_back(ySS.str());

        //send telegram
        Message message(playerId_ , playerId_, moveParameters);
        Telegram telegram(playerId_, playerId_, 0.0, message);
        core_->getMessageCentre()->addTelegram(telegram);
    }

    if(input_->IsMouseButtonDown(sf::Mouse::Right))
    {

        //get player trigger comp if it has one (It should do!)
        TriggerComp* playerTriggerComp = core_->getTriggerSub()->getComponent(playerId_);
        if (playerTriggerComp)
        {
            //prepare message to send TODO: Currently hard coded (like "guns" below) but would be fairly simple to make configurable in xml
//            Parameters launchParams;
//            launchParams.push_back("launcher");
//            launchParams.push_back("launch");


            //TODO: This is currently hard coded, but needn't be
            std::vector<ObjectId> ids = playerTriggerComp->getTriggeredObjects("guns");
            std::vector<Parameters> launchParams = playerTriggerComp->getTriggeredParameters("guns");
            std::cout << "There are " << ids.size() << " target objects for guns message" << std::endl;
            std::vector<ObjectId>::iterator iId = ids.begin();
            while(iId!=ids.end())
            {
                std::cout << "Processing message for object "<< *iId << std::endl;
                //for each set of message params, send a message
                std::vector<Parameters>::iterator iParams = launchParams.begin();
                while(iParams != launchParams.end())
                {
                    //bundle message and send it
                    Message launchMsg(playerId_, *iId, *iParams);
                    Telegram launchTelegram(playerId_, *iId,0.0, launchMsg);
                    core_->getMessageCentre()->addTelegram(launchTelegram);
                    ++iParams;
                }
                ++iId;
            }
        }
        //get launcher and launch if exists
        //grab corresponding Coords comp
//        LauncherComp* launcherComp = core_->getLauncherSub()->getComponent(playerId_);
//        if (launcherComp)
//        {
//            Parameters launchParams;
//            launchParams.push_back("launcher");
//            launchParams.push_back("launch");
//
//
//            Message launchMessage(playerId_, playerId_, launchParams);
//            Telegram launchTelegram(playerId_, playerId_, 0.0, launchMessage);
//            //send messages
//            core_->getMessageCentre()->addTelegram(launchTelegram);
//        }


    }
}
