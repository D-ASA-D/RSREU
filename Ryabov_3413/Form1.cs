using System;
using System.Drawing;
using System.Windows.Forms;

namespace Ryabov_3413
{
    public partial class Form1 : Form
    {
        private CharacterConfig config = new CharacterConfig()
        {
            Size = new Size(400, 400),
            HairColor = Color.Purple,
            HairPoints = new Point[]
            {
                new Point(100, 150), new Point(160, 110), new Point(190, 30),
                new Point(250, 90), new Point(310, 30), new Point(340, 110),
                new Point(400, 150), new Point(300, 235), new Point(200, 300),
                new Point(225, 245)
            },
            BodyColor = Color.Pink,
            BodyBounds = new Rectangle(150, 100, 200, 200),
            Ears = new Ear[]
            {
                new Ear { Bounds = new Rectangle(140, 150, 40, 30) },
                new Ear { Bounds = new Rectangle(320, 150, 40, 30) }
            },
            Eyes = new Eye[]
            {
                new Eye { Position = new Point(210, 170), Size = new Size(50, 50),
                         PupilSize = new Size(20, 20), HighlightSize = new Size(5, 5) },
                new Eye { Position = new Point(270, 170), Size = new Size(50, 50),
                         PupilSize = new Size(20, 20), HighlightSize = new Size(5, 5) }
            },
            Glasses = new Glasses
            {
                FrameSize = new Size(60, 60),
                FrameThickness = 8,
                BridgeLength = 60
            },
            Limbs = new Limb[]
            {
                new Limb { Bounds = new Rectangle(140, 210, 20, 60) },
                new Limb { Bounds = new Rectangle(340, 210, 20, 60) },
                new Limb { Bounds = new Rectangle(190, 265, 50, 70) },
                new Limb { Bounds = new Rectangle(270, 265, 50, 70) }
            },
            Lines = new Line[]
            {
                new Line {
                    Start = new Point(162, 150),
                    End = new Point(205, 200),
                    Color = Color.Black,
                    Width = 8
                },
                new Line {
                    Start = new Point(325, 200),
                    End = new Point(335, 148),
                    Color = Color.Black,
                    Width = 8
                }
            },
            Triangle = new Triangle
            {
                Points = new Point[]
                {
                    new Point(255, 225),
                    new Point(275, 225),
                    new Point(265, 240)
                },
                Color = Color.Black
            },
            TopLine = new Line
            {
                Start = new Point(265, 230),
                End = new Point(265, 252),
                Color = Color.Black,
                Width = 3
            },
            TopTriangles = new Triangle[]
            {
                new Triangle
                {
                    Points = new Point[]
                    {
                        new Point(265, 250),
                        new Point(265, 255),
                        new Point(250, 245)
                    },
                    Color = Color.Black
                },
                new Triangle
                {
                    Points = new Point[]
                    {
                        new Point(265, 250),
                        new Point(265, 255),
                        new Point(280, 245)
                    },
                    Color = Color.Black
                }
            }
        };

        public Form1()
        {
            InitializeComponent();
            SetupForm();
        }

        private void SetupForm()
        {
            this.Text = "Рябов Владислав. гр.3413";
            this.ClientSize = config.Size;
            this.DoubleBuffered = true;
            this.BackColor = Color.White;
            this.Paint += Form1_Paint;
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            DrawCharacter(e.Graphics);
        }

        private void DrawCharacter(Graphics g)
        {
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            var outlinePen = new Pen(Color.Black, 2);

            // Волосы с контуром
            using (var hairBrush = new SolidBrush(config.HairColor))
            {
                g.FillPolygon(hairBrush, config.HairPoints);
                g.DrawPolygon(outlinePen, config.HairPoints);
            }

            // Конечности с контуром
            using (var bodyBrush = new SolidBrush(config.BodyColor))
            {
                foreach (var limb in config.Limbs)
                {
                    g.FillEllipse(bodyBrush, limb.Bounds);
                    g.DrawEllipse(outlinePen, limb.Bounds);
                }
            }

            // Уши с контуром
            using (var bodyBrush = new SolidBrush(config.BodyColor))
            {
                foreach (var ear in config.Ears)
                {
                    g.FillEllipse(bodyBrush, ear.Bounds);
                    g.DrawEllipse(outlinePen, ear.Bounds);
                }
            }

            // Тело с контуром
            using (var bodyBrush = new SolidBrush(config.BodyColor))
            {
                g.FillEllipse(bodyBrush, config.BodyBounds);
                g.DrawEllipse(outlinePen, config.BodyBounds);
            }



            // Глаза с контуром
            DrawEyes(g, outlinePen);



            // Линии
            foreach (var line in config.Lines)
            {
                using (var pen = new Pen(line.Color, line.Width))
                {
                    g.DrawLine(pen, line.Start, line.End);
                }
            }

            // Треугольник с контуром
            using (var triangleBrush = new SolidBrush(config.Triangle.Color))
            {
                g.FillPolygon(triangleBrush, config.Triangle.Points);
                g.DrawPolygon(outlinePen, config.Triangle.Points);
            }

            // Верхняя линия
            using (var topLinePen = new Pen(config.TopLine.Color, config.TopLine.Width))
            {
                g.DrawLine(topLinePen, config.TopLine.Start, config.TopLine.End);
            }

            // Верхние треугольники с контуром
            foreach (var triangle in config.TopTriangles)
            {
                using (var triangleBrush = new SolidBrush(triangle.Color))
                {
                    g.FillPolygon(triangleBrush, triangle.Points);
                    g.DrawPolygon(outlinePen, triangle.Points);
                }
            }

            outlinePen.Dispose();
        }

        private void DrawEyes(Graphics g, Pen outlinePen)
        {
            using (var pupilBrush = new SolidBrush(Color.Black))
            using (var highlightBrush = new SolidBrush(Color.White))
            using (var glassesPen = new Pen(Color.Black, config.Glasses.FrameThickness))
            {
                for (int i = 0; i < config.Eyes.Length; i++)
                {
                    var eye = config.Eyes[i];
                    var eyeRect = new Rectangle(eye.Position.X, eye.Position.Y,
                                              eye.Size.Width, eye.Size.Height);

                    g.FillEllipse(Brushes.White, eyeRect);
                    g.DrawEllipse(outlinePen, eyeRect);

                    g.FillEllipse(pupilBrush,
                        eye.Position.X + (eye.Size.Width - eye.PupilSize.Width) / 2,
                        eye.Position.Y + (eye.Size.Height - eye.PupilSize.Height) / 2,
                        eye.PupilSize.Width, eye.PupilSize.Height);

                    g.FillEllipse(highlightBrush,
                        eye.Position.X + eye.Size.Width / 3,
                        eye.Position.Y + eye.Size.Height / 3,
                        eye.HighlightSize.Width, eye.HighlightSize.Height);

                    if (i == 0)
                    {
                        var glassesFrame = new Rectangle(
                            eye.Position.X - (config.Glasses.FrameSize.Width - eye.Size.Width) / 2,
                            eye.Position.Y - (config.Glasses.FrameSize.Height - eye.Size.Height) / 2,
                            config.Glasses.FrameSize.Width,
                            config.Glasses.FrameSize.Height);

                        g.DrawEllipse(glassesPen, glassesFrame);
                        var rightFrame = glassesFrame;
                        rightFrame.X += config.Glasses.BridgeLength;
                        g.DrawEllipse(glassesPen, rightFrame);
                        g.DrawLine(glassesPen,
                                 glassesFrame.X + glassesFrame.Width,
                                 glassesFrame.Y + glassesFrame.Height / 2,
                                 rightFrame.X,
                                 rightFrame.Y + rightFrame.Height / 2);
                    }
                }
            }
        }
    }

    public class Line
    {
        public Point Start { get; set; }
        public Point End { get; set; }
        public Color Color { get; set; }
        public float Width { get; set; }
    }

    public class Triangle
    {
        public Point[] Points { get; set; }
        public Color Color { get; set; }
    }

    public class CharacterConfig
    {
        public Size Size { get; set; }
        public Color HairColor { get; set; }
        public Point[] HairPoints { get; set; }
        public Color BodyColor { get; set; }
        public Rectangle BodyBounds { get; set; }
        public Ear[] Ears { get; set; }
        public Eye[] Eyes { get; set; }
        public Glasses Glasses { get; set; }
        public Limb[] Limbs { get; set; }
        public Line[] Lines { get; set; }
        public Triangle Triangle { get; set; }
        public Line TopLine { get; set; }
        public Triangle[] TopTriangles { get; set; }
    }

    public class Ear
    {
        public Rectangle Bounds { get; set; }
    }

    public class Eye
    {
        public Point Position { get; set; }
        public Size Size { get; set; }
        public Size PupilSize { get; set; }
        public Size HighlightSize { get; set; }
    }

    public class Glasses
    {
        public Size FrameSize { get; set; }
        public int FrameThickness { get; set; }
        public int BridgeLength { get; set; }
    }

    public class Limb
    {
        public Rectangle Bounds { get; set; }
    }
}