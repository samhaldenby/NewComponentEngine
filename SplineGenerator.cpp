#include "SplineGenerator.h"

void SplineGenerator::drawSpline(Path p,int x, int y)
{
    sf::RenderWindow App(sf::VideoMode(x, y, 32), "SFML Graphics");

    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

        // Clear the screen (fill it with black color)
        App.Clear();

        //Draw path
        Path::iterator iPath = p.begin();
        Vector2d prevPoint = *iPath;
        ++iPath;
        while(iPath!=p.end())
        {
            Vector2d currPoint = *iPath;
            sf::Shape line   = sf::Shape::Line(prevPoint.x * x, prevPoint.y * y,currPoint.x * x , currPoint.y * y, 1, sf::Color::Red);
            App.Draw(line);
            ++iPath;
            prevPoint = currPoint;
        }

        // Display window contents on screen
        App.Display();
    }
}

Path SplineGenerator::makeBezier(int points, int nodes, int seed)
{
    srand(seed);
    Path path;
    int minDist = 0.35355;
    std::cout << "MinDist: " << minDist << std::endl;
    Vector2d start(randf(),0);
    Vector2d end(randf(),1);

    for (int node=0 ; node < nodes ; ++node)
    {

        Vector2d p0 = start;
        Vector2d p1(randf(), randf());
//        Vector2d p1(rand()%w,rand()%h);
        Vector2d p2(randf(), randf());
        Vector2d p3(randf(), randf());
        while(p3.getDistance(p1)<minDist)
        {
            p3.x = randf();
            p3.y = randf();
        }

        int pointsPerNode = points / nodes;
        for (int x=0; x<pointsPerNode;++x)
        {
            float t = x/float(pointsPerNode);
            Vector2d res= calculateBezierPoint(t,p0,p1,p2,p3);
            path.push_back(res);
        }

        start = p3;
    }

    //do last link
//    Vector2d p0 = start;
//    Vector2d p1(rand()%w,rand()%h);
//    Vector2d p2(rand()%w,rand()%h);
//    Vector2d p3 = end;
//    for (int x=0; x<steps;++x)
//    {
//        float t = x/float(steps);
//        Vector2d res= calculateBezierPoint(t,p0,p1,p2,p3);
//        if (x!=0)
//        {
//            out << t << "\t" << res.x <<"\t" << res.y << std::endl;
//        }
//        else
//        {
//            out << t << "\t" << res.x <<"\t" << res.y << "\t" << start.x << "\t" << start.y << std::endl;
//        }
//    }




    //end test for bezier curving
    return path;
}



Path SplineGenerator::makeCatmul(int points, int nodes, int seed)
{
    srand(seed);
    Path path;
    //test for catmull

    Vector2d p0(randf(),0);
    Vector2d p1(randf(),0);
    Vector2d p2(randf(),0);
    Vector2d p3(randf(),0);

    int pointsPerNode = points/nodes;

    for (int node=0; node<nodes; ++node)
    {
        Vector2d next(randf(),randf());
        Vector2d next2(randf(),randf());
        //works ok - quite roundy
        p0=p1;
        p1=p2;
        p2=p3;
        p3=next;
        //works ok - more roundy
//        p0=p1;
//        p1=p2;
//        p2=next;
//        p3=next2;

        for (int x=0;x<pointsPerNode;++x)
        {
            float t = x/float(pointsPerNode);
            Vector2d r = calculateCatmullPoint(t,p0,p1,p2,p3);
            path.push_back(r);

            std::cout << r.x << "\t" << r.y << "\t" << std::endl;


        }
    }

    return path;
}


Vector2d SplineGenerator::calculateBezierPoint(float t, Vector2d p0, Vector2d p1, Vector2d p2, Vector2d p3)
{
    float u   = 1 - t;
    float tt  = t * t;
    float uu  = u * u;
    float uuu = u * u * u;
    float ttt = t * t * t;

    Vector2d p = p0 * uuu; //first term
    p += p1 * (uu * 3  * t); //second term
    p += p2 * (3 * u * tt) ; //third term
    p += p3 * ttt; //fourth term

    return p;
}


////////////
//p1 and p2 define section
//t is proprtion across p1-p2
//p3 and p0 bend the curve, I guess!
Vector2d SplineGenerator::calculateCatmullPoint(float t,
                               Vector2d p0,
                               Vector2d p1,
                               Vector2d p2,
                               Vector2d p3)
{
    float tt  = t * t;
    float ttt = tt * t;
    Vector2d p;
    p.x = 0.5f * ((p1.x * 2.0f) + (p2.x - p0.x) * t +
    (p0.x * 2.0f - p1.x * 5.0f + p2.x * 4.0f - p3.x) * tt +
    (p0.x * -1.0f + p1.x * 3.0f + p2.x * -3.0f + p3.x) * ttt);

    p.y = 0.5f * ((p1.y * 2.0f) + (p2.y - p0.y) * t +
    (p0.y * 2.0f - p1.y * 5.0f + p2.y * 4.0f - p3.y) * tt +
    (p0.y * -1.0f + p1.y * 3.0f + p2.y * -3.0f + p3.y) * ttt);

    return p;
}
