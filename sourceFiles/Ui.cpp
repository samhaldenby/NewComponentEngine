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
        //get launcher and launch if exists
        //grab corresponding Coords comp
        LauncherComp* launcherComp = core_->getLauncherSub()->getComponent(playerId_);
        if (launcherComp)
        {
            Parameters launchParams;
            launchParams.push_back("launcher");
            launchParams.push_back("launch");
            Message launchMessage(playerId_, playerId_, launchParams);
            Telegram launchTelegram(playerId_, playerId_, 0.0, launchMessage);
            //send messages
            core_->getMessageCentre()->addTelegram(launchTelegram);
        }

//        //create telegram for shooting a bullet
//        ObjectId bulletId = core_->getObjectBuilder()->createObject("simpleBullet");
//        Parameters changePosParams;
//        changePosParams.push_back("coords");
//        changePosParams.push_back("setCoords");
//        std::stringstream xSS(""), ySS("");
//        CoordsComp* playerCoordsComp = core_->getCoordsSub()->getComponent(playerId_);
//        xSS << playerCoordsComp->getCoords().x;
//        ySS << playerCoordsComp->getCoords().y;
//        changePosParams.push_back(xSS.str());
//        changePosParams.push_back(ySS.str());
//        Message changePosMessage(bulletId, bulletId, changePosParams);
//        Telegram changePosTelegram(bulletId, bulletId, 0.0, changePosMessage);
//
//        //set move
//        Parameters bulletSpeedParams;
//        bulletSpeedParams.push_back("move");
//        bulletSpeedParams.push_back("setVelocity");
//        bulletSpeedParams.push_back("0");
//        bulletSpeedParams.push_back("-2");
//        Message bulletSpeedMessage(bulletId, bulletId, bulletSpeedParams);
//        Telegram bulletSpeedTelegram(bulletId, bulletId, 0.0, bulletSpeedMessage);
//
//        //send messages
//        core_->getMessageCentre()->addTelegram(changePosTelegram);
//        core_->getMessageCentre()->addTelegram(bulletSpeedTelegram);


//        Parameters changeGfxParams = core_->getStore()->getMessageParameters("changeSprite");
//        changeGfxParams.push_back("coin.png");
//        Message message(iCom->second.getId(), iCom->second.getId(), changeGfxParams);
//        Telegram telegram(iCom->second.getId(), iCom->second.getId(), 0.0, message);
//        core_->getMessageCentre()->addTelegram(telegram);
    }
}
