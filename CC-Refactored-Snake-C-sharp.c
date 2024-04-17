using System;
using System.Collections.Generic;
using System.Threading;

namespace SnakeGame
{
    class Program
    {
        static void Main()
        {
            Game game = new Game();
            game.Setup();
            game.Start();
        }
    }

    class Game
    {
        private const int ScreenWidth = 32;
        private const int ScreenHeight = 16;
        private int score = 0;
        private bool gameOver = false;
        private Pixel head;
        private Pixel berry;
        private List<Pixel> body = new List<Pixel>();
        private Direction movement = Direction.Right;
        private Random random = new Random();

        public void Setup()
        {
            Console.WindowHeight = ScreenHeight;
            Console.WindowWidth = ScreenWidth;
            head = new Pixel(ScreenWidth / 2, ScreenHeight / 2, ConsoleColor.Red);
            PlaceBerry();
        }

        public void Start()
        {
            while (!gameOver)
            {
                Draw();
                Input();
                Logic();
                Thread.Sleep(100); // Adjust for game speed
            }

            Console.SetCursorPosition(ScreenWidth / 4, ScreenHeight / 2);
            Console.WriteLine($"Game over, Score: {score}");
        }

        private void Draw()
        {
            Console.Clear();
            DrawBorders();
            DrawPixel(berry);
            foreach (Pixel segment in body)
            {
                DrawPixel(segment);
            }
            DrawPixel(head);
        }

        private void Input()
        {
            if (Console.KeyAvailable)
            {
                ConsoleKey key = Console.ReadKey(true).Key;
                ChangeDirection(key);
            }
        }

        private void Logic()
        {
            MoveSnake();
            CheckCollisions();
            CheckBerryCollision();
        }

        private void DrawBorders()
        {
            Console.ForegroundColor = ConsoleColor.White;
            for (int i = 0; i < ScreenWidth; i++)
            {
                Console.SetCursorPosition(i, 0);
                Console.Write("■");
                Console.SetCursorPosition(i, ScreenHeight - 1);
                Console.Write("■");
            }
            for (int i = 0; i < ScreenHeight; i++)
            {
                Console.SetCursorPosition(0, i);
                Console.Write("■");
                Console.SetCursorPosition(ScreenWidth - 1, i);
                Console.Write("■");
            }
        }

        private void DrawPixel(Pixel pixel)
        {
            Console.SetCursorPosition(pixel.XPos, pixel.YPos);
            Console.ForegroundColor = pixel.Color;
            Console.Write("■");
        }

        private void ChangeDirection(ConsoleKey key)
        {
            switch (key)
            {
                case ConsoleKey.UpArrow when movement != Direction.Down:
                    movement = Direction.Up;
                    break;
                case ConsoleKey.DownArrow when movement != Direction.Up:
                    movement = Direction.Down;
                    break;
                case ConsoleKey.LeftArrow when movement != Direction.Right:
                    movement = Direction.Left;
                    break;
                case ConsoleKey.RightArrow when movement != Direction.Left:
                    movement = Direction.Right;
                    break;
            }
        }

        private void MoveSnake()
        {
            body.Add(new Pixel(head.XPos, head.YPos, ConsoleColor.Green));

            switch (movement)
            {
                case Direction.Up:
                    head.YPos--;
                    break;
                case Direction.Down:
                    head.YPos++;
                    break;
                case Direction.Left:
                    head.XPos--;
                    break;
                case Direction.Right:
                    head.XPos++;
                    break;
            }

            if (body.Count > score)
            {
                body.RemoveAt(0);
            }
        }

        private void CheckCollisions()
        {
            if (head.XPos == 0 || head.XPos == ScreenWidth - 1 || head.YPos == 0 || head.YPos == ScreenHeight - 1)
            {
                gameOver = true;
            }

            foreach (Pixel segment in body)
            {
                if (segment.XPos == head.XPos && segment.YPos == head.YPos)
                {
                    gameOver = true;
                }
            }
        }

        private void CheckBerryCollision()
        {
            if (head.XPos == berry.XPos && head.YPos == berry.YPos)
            {
                score++;
                PlaceBerry();
            }
        }

        private void PlaceBerry()
        {
            int x = random.Next(1, ScreenWidth - 1);
            int y = random.Next(1, ScreenHeight - 1);
            berry = new Pixel(x, y, ConsoleColor.Cyan);
        }
    }

    class Pixel
    {
        public int XPos { get; set; }
        public int YPos { get; set; }
        public ConsoleColor Color { get; set; }

        public Pixel(int x, int y, ConsoleColor color)
        {
            XPos = x;
            YPos = y;
            Color = color;
        }
    }

    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    }
}
