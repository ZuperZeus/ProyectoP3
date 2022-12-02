/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Connect4Scene.h"
#include "Board.h"
#include <windows.h>
#include <mmsystem.h>
#include "HelloWorldScene.h"
USING_NS_CC;
int color;
Scene* Connect4::createScene(int x)
{
    color = x;
    log("COLOR:%d",color);
    return Connect4::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Connect4Scene.cpp\n");
}
void Connect4::placePiece(int p, int x, int y)
{
    auto play = Sprite::create("player2" + ("_cs" + std::to_string(color)) + ".png");
    if (p == 1)
    {
        play = Sprite::create("player1" + ("_cs" + std::to_string(color)) + ".png");
    }
    play->setPosition(Vec2(100 * x + 50, 100 * (5-y) + 50));
    this->addChild(play, 1);
}
void Connect4::showWin()
{
    std::vector< std::vector<int> > win = board.getWin();
    for (int i = 0; i < win[0].size(); i++)
    {
        auto piece = Sprite::create("winsel.png");
        piece->setPosition(Vec2(100 * win[0][i] + 50, 100 * (5 - win[1][i]) + 50));
        this->addChild(piece, 1);
    }
}
void Connect4::play(int x)
{
    if (board.canDrop(x))
    {
        int win = board.checkWin();
        if (win == 0)
        {
            turn = 3 - turn;
            placePiece(turn, x, board.drop(x, turn));
            scoreint++;
            auto top = Sprite::create("top.png");
            top->setPosition(Vec2(350,650));
            this->addChild(top, 2);
            auto score = Label::createWithTTF((std::string)("Score: "+std::to_string(scoreint)), "fonts/Marker Felt.ttf", 50);
            score->setPosition(Vec2(100, 650));
            this->addChild(score, 2);
            auto trn = Label::createWithTTF((std::string)("Player " + std::to_string(3-turn)), "fonts/Marker Felt.ttf", 50);
            trn->setPosition(Vec2(600, 650));
            this->addChild(trn, 2);
        }
        win = board.checkWin();
        auto label = Label::createWithTTF("Player 2 WON!!!", "fonts/Marker Felt.ttf", 100);
        if(win==1) label = Label::createWithTTF("Player 1 WON!!!", "fonts/Marker Felt.ttf", 100);
        if(win!=0&&gameRunning)
        {
            PlaySound(TEXT("winsound.wav"), NULL, SND_FILENAME | SND_ASYNC);
            auto ovw = Sprite::create("board" + ("_cs" + std::to_string(color)) + ".png");
            ovw->setPosition(Vec2(350, 300));
            this->addChild(ovw, 1);
            showWin();
            auto win = Sprite::create("win.png");
            win->setPosition(Vec2(350, 300));
            this->addChild(win, 1);
            if (label == nullptr)
            {
                problemLoading("'fonts/Marker Felt.ttf'");
            }
            else
            {
                label->setPosition(Vec2(350,300));
                this->addChild(label, 2);
            }
            gameRunning = false;
        }
        
    }/*
    std::vector<int> test;
    int col;
    if (x == 0) { col = col0; col0++; }
    else if (x == 1) { col = col1; col1++; }
    else if (x == 2) { col = col2; col2++; }
    else if (x == 3) { col = col3; col3++; }
    else if (x == 4) { col = col4; col4++; }
    else if (x == 5) { col = col5; col5++; }
    else if (x == 6) { col = col6; col6++; }
    if (col <= 5)
        turn = 3 - turn;
    placePiece(turn, x, col);
    */
    //if (getNumAt(x, 0) == 0) placePiece(turn, x, 0);
    //else if (getNumAt(x, 1) == 1) placePiece(turn, x, 1);

       
}
void Connect4::updateSel()
{
    auto ovw = Sprite::create("board" + ("_cs" + std::to_string(color)) + ".png");
    //auto ovw = Sprite::create("board_cs3.png");
    ovw->setPosition(Vec2(350,300));
    this->addChild(ovw, 1);
    auto selec = Sprite::create("sel" + ("_cs" + std::to_string(color)) + ".png");
    selec->setPosition(Vec2(100*currsel+50,300));
    this->addChild(selec, 1);
}
void Connect4::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (gameRunning == false)
    {
        Scene* tempScene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(tempScene);
    }
    if (board.checkWin() == 0)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)currsel += 6;
        else if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)currsel++;
        currsel = currsel % 7;
        updateSel();
        if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) play(currsel);
    }
}
// on "init" you need to initialize your instance
bool Connect4::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    Director::getInstance()->getOpenGLView()->setFrameSize(700, 700);
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(700, 700, ResolutionPolicy::EXACT_FIT);
   
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //placePiece(1, 3, 4);
    //placePiece(2, 0, 0);
    //placePiece(2, 6, 5);
    updateSel();
    EventKeyboard::KeyCode;
    auto listener = EventListenerKeyboard::create();
        //CC_CALLBACK_2(Connect4::onKeyPressed, this);
    listener->onKeyPressed = CC_CALLBACK_2(Connect4::onKeyPressed, this);
   
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    auto score = Label::createWithTTF((std::string)("Score: " + std::to_string(scoreint)), "fonts/Marker Felt.ttf", 50);
    score->setPosition(Vec2(100, 650));
    this->addChild(score, 2);
    auto trn = Label::createWithTTF((std::string)("Player " + std::to_string(3-turn)), "fonts/Marker Felt.ttf", 50);
    trn->setPosition(Vec2(600, 650));
    this->addChild(trn, 2);

    //auto p1 = Sprite::create("player1" + ("_cs" + std::to_string(color)) + ".png");
    //p1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //this->addChild(p1, 1);
    //auto p2 = Sprite::create("player2.png");
    //p2->setPosition(Vec2(100*6 +50+origin.x, 100*5 +50+origin.y));
    //this->addChild(p2, 2);
    // add a "close" icon to exit the progress. it's an autorelease object
    
    /*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Connect4::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    


    // add "Connect4" splash screen"
    auto sprite = Sprite::create("board.png");
    if (sprite == nullptr)
    {
        auto label = Label::createWithTTF("ERROR", "fonts/Marker Felt.ttf", 24);
        if (label == nullptr)
        {
            problemLoading("'fonts/Marker Felt.ttf'");
        }
        else
        {
            // position the label on the center of the screen
            label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                origin.y + visibleSize.height - label->getContentSize().height));

            // add the label as a child to this layer
            this->addChild(label, 1);
        }
        problemLoading("'Connect4.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
        auto label = Label::createWithTTF("NAERROR", "fonts/Marker Felt.ttf", 24);
        if (label == nullptr)
        {
            problemLoading("'fonts/Marker Felt.ttf'");
        }
        else
        {
            // position the label on the center of the screen
            label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                origin.y + visibleSize.height - label->getContentSize().height));

            // add the label as a child to this layer
            this->addChild(label, 1);
        }
    }*/
    return true;
}


void Connect4::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
