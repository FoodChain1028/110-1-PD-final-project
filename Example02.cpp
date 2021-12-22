//#include<SFML/Graphics.hpp>
//using namespace sf;
// //呼叫視窗
//int main()
//{
//    RenderWindow window(VideoMode(800, 600), "My window");// for size, "name"
//    window.setFramerateLimit(60); // limit fps to prevent overloading on graphic card.
//
//    CircleShape shape(50.f); // 呼叫一個 圓形 叫做 shape
// 
//
//        // run the program as long as the window is open
//        while (window.isOpen()) // if not, it'll shut down as soon as you open it
//        {
//            // check all the window's events that were triggered since the last iteration of the loop
//            Event event;
//            while (window.pollEvent(event))
//            {
//                // "close requested" event: we close the window
//                if (event.type == Event::Closed)
//                    window.close();
//            }
//
//            // Update: for charcters [press w] -> [move forward]
//            // you have to update the screen to see the position change.
//            shape.move(2.5f, 0.f); //讓圓形可以動
//
//            // Draw: draw new things on the 
//            //window.clear(); // 每一次畫的時候都需要把原本的清掉 
//
//            window.draw(shape);
//
//            window.display();// 就是展示你前面做的更新 & draw
//        }
//
//    return 0;
//}