//#include<SFML/Graphics.hpp>
//using namespace sf;
// //�I�s����
//int main()
//{
//    RenderWindow window(VideoMode(800, 600), "My window");// for size, "name"
//    window.setFramerateLimit(60); // limit fps to prevent overloading on graphic card.
//
//    CircleShape shape(50.f); // �I�s�@�� ��� �s�� shape
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
//            shape.move(2.5f, 0.f); //����Υi�H��
//
//            // Draw: draw new things on the 
//            //window.clear(); // �C�@���e���ɭԳ��ݭn��쥻���M�� 
//
//            window.draw(shape);
//
//            window.display();// �N�O�i�ܧA�e��������s & draw
//        }
//
//    return 0;
//}