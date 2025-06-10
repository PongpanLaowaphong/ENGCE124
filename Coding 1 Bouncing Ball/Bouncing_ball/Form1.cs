using System;
using System.Drawing;
using System.Windows.Forms;

namespace Bouncing_ball
{
    public partial class Form1 : Form
    {

        //กำหนดตัวแปรต่างที่จะใช้งานในโปรแกรม

        private int ballWidth = 40; // ความกว้างของลูกบอล มีหน่วยเป็น พิกเซล
        private int ballHeight = 40; // ความสูงของลูกบอล มีหน่วยเป็น พิกเซล
        private float ballPosX = 0; // ตำแหน่งลูกบอลบนแกน X
        private float ballPosY = 0; // ตำแหน่งลูกบอลบนแกน Y
        private float moveStepX = 8; // [ค่ามาตรฐาน : 4] ความเร็วการเลื่อนของลูกบอลบนแกน X มีหน่วยเป็น พิกเซล
        private int moveStepY = 8; // [ค่ามาตรฐาน : 4] ความเร็วการเลื่อนของลูกบอลบนแกน Y มีหน่วยเป็น พิกเซล
        private System.Windows.Forms.Timer ballTimer; // จับเวลาสำหรับภาพเคลื่อนไหวของลูกบอล

        private int paddleWidth = 300; // ความกว้างของแป้น มีหน่วยเป็น พิกเซล
        private int paddleHeight = 5; // ความสูงของแป้น มีหน่วยเป็น พิกเซล
        private int paddlePosX; // ตำแหน่งแป้นบนแกน X
        private int paddlePosY; // ตำแหน่งแป้นบนแกน Y
        private int paddleMoveStep = 32; // [ค่ามาตรฐาน : 8] ความเร็วการเลื่อนของแป้น มีหน่วยเป็น พิกเซล
        private System.Windows.Forms.Timer paddleTimer; // จับเวลาสำหรับภาพเคลื่อนไหวของแป้น

        private bool isLeftPressed = false; // ติดตามว่ากดปุ่มลูกศรซ้ายถูกกด
        private bool isRightPressed = false; // ติดตามว่ากดปุ่มลูกศรขวาถูกกด

        private bool isUpPressed = false; // ติดตามว่ากดปุ่มลูกศรบนถูกกด
        private bool isDownPressed = false; // ติดตามว่ากดปุ่มลูกศรล่างถูกกด

        Random ran = new Random(); // สำหรับการสุ่มตำแหน่งการเกิดของลูกบอลหรือแป้น

        int score = 0;


        public Form1()
        {
            InitializeComponent();

            // ใช้งานฟังก์ชันที่มีชื่อว่า Form1_Load
            this.Load += new EventHandler(Form1_Load);

            // ตั้งค่าบัฟเฟอร์สองเท่าเพื่อลดการสั่นไหว [ใช้เงื่อนไขนี้เพื่อให้ลูกบอลเคลื่อนที่มีความลื่นไหล]
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer | ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint, true);
            this.UpdateStyles();

            // เริ่มต้นจับเวลาลูกบอล เวลาเคลื่อนที่
            // การจับเวลาจะทำให้เกิดการอัปเดตตำแหน่งของลูกบอลเป็นระยะๆ ตามช่วงเวลาที่กำหนด
            ballTimer = new System.Windows.Forms.Timer();
            ballTimer.Interval = 30; // ตั้งค่าช่วงเวลา มีหน่วยเป็น มิลลิวินาที
            ballTimer.Tick += new EventHandler(MoveBall); //การใช้งานฟังก์ชัน Moveball ที่มีผลกับการจับเวลา
            ballTimer.Start(); //เริ่มต้นการจับเวลา

            // เริ่มต้นจับเวลาแป้น เวลาเคลื่อนที่
            // การจับเวลาจะทำให้เกิดการอัปเดตตำแหน่งของลูกบอลเป็นระยะๆ ตามช่วงเวลาที่กำหนด
            paddleTimer = new System.Windows.Forms.Timer();
            paddleTimer.Interval = 15; // ตั้งค่าช่วงเวลา มีหน่วยเป็น มิลลิวินาที
            paddleTimer.Tick += new EventHandler(MovePaddle); //การใช้งานฟังก์ชัน Movepaddle ที่มีผลกับการจับเวลา


            //สุ่มตำแหน่งการเกิดของลูกบอล
            float BallRanposition = ran.Next(1,4);
            int PaddleRanposition = ran.Next(1,4);

            // กำหนดตำแหน่งลูกบอลตอนเริ่มต้น
    
            ballPosX = (this.ClientSize.Width - ballWidth) / BallRanposition; // [ค่ามาตรฐาน : 2] กำหนดตำแหน่งในแนวนอนของลูกบอล
            ballPosY = (this.ClientSize.Height - ballHeight) / BallRanposition; // [ค่ามาตรฐาน : 2] กำหนดตำแหน่งในแนวตั้งของลูกบอล

            // กำหนดตำแหน่งแป้นตอนเริ่มต้น
            paddlePosX = (this.ClientSize.Width - paddleWidth) / PaddleRanposition; // [ค่ามาตรฐาน : 1] กำหนดตำแหน่งในแนวนอนของแป้น
            paddlePosY = this.ClientSize.Height - paddleHeight + PaddleRanposition; // [ค่ามาตรฐาน : 500] กำหนดตำแหน่งในแนวตั้งของแป้น

            // ใช้งานฟังก์ชัน Paintcircle
            this.Paint += new PaintEventHandler(PaintCircle);

            // ใช้งานฟังก์ชัน OnKeyDown และ ฟังก์ชัน OnKeyDown
            this.KeyDown += new KeyEventHandler(OnKeyDown);
            this.KeyUp += new KeyEventHandler(OnKeyUp);

        }

        private void PaintCircle(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias; // ทำให้กรอบของลูกบอลเรียบขึ้น

            e.Graphics.Clear(this.BackColor); // ล้างพื้นที่วาดด้วยสีพื้นหลังของฟอร์ม

            // เรียกใช้งานเมธอดของการวาดรูปลูกบอล
            PaintBall(e.Graphics);

            // เรียกใช้งานเมธอดของการวาดรูปแป้น
            PaintPaddle(e.Graphics);

            // เรียกใช้งานเมธอดของการวาดรูป เขียนชื่อผู็ทำ
            PongpanLaowaphong(e.Graphics);

        }

        private void PaintBall(Graphics graphics)
        {
            // วาดลูกบอลขึ้นมาให้เป็นสีแดง
            graphics.FillEllipse(Brushes.Red, ballPosX, ballPosY, ballWidth, ballHeight);

            // ใส่กรอบสีดำให้กับลูกบอล
            graphics.DrawEllipse(Pens.Black, ballPosX, ballPosY, ballWidth, ballHeight);

        }

        private void PongpanLaowaphong(Graphics graphics)
        {

            // เขียนข้อความ "Pongpan Laowaphong [66543206019-2]"
            string message = $"Pongpan Laowaphong [66543206019-2] \nScore from hit the paddle : {score}";
            Font font = new Font("Arial", 24, FontStyle.Bold);
            SizeF textSize = graphics.MeasureString(message, font);

            // กำหนดตำแหน่งให้กับตัวหนังสือ (กำหนดไว้ซ้ายบน)
            float x = (this.ClientSize.Width - textSize.Width) / 40;
            float y = (this.ClientSize.Height - textSize.Height) / 25;

            graphics.DrawString(message, font, Brushes.Black, x, y);

        }

        private void PaintPaddle(Graphics graphics)
        {
            // วาดแป้นขึ้นมาให้เป็นสีน้ำเงิน
            graphics.FillRectangle(Brushes.Blue, paddlePosX, paddlePosY, paddleWidth, paddleHeight);
        }
        private void MoveBall(object sender, EventArgs e)
        {
            
            // อัปเดตตำแหน่งของลูกบอล
            ballPosX += moveStepX;
            ballPosY += moveStepY;

            // ตรวจสอบการชนของวัตถุกับขอบหน้าจอ และสะท้อนกับไปในทิศทางตรงกันข้าม
            if (ballPosX < 0 || ballPosX + ballWidth > this.ClientSize.Width)
            {
                moveStepX = -moveStepX;
            }

            if (ballPosY < 0 || ballPosY + ballHeight > this.ClientSize.Height)
            {
                moveStepY = -moveStepY;

            }

            //  ตรวจสอบการชนของวัตถุกับแป้น และสะท้อนกับไปในทิศทางตรงกันข้าม
            if (ballPosX + ballWidth > paddlePosX && ballPosX < paddlePosX + paddleWidth &&
                ballPosY + ballHeight > paddlePosY && ballPosY < paddlePosY + paddleHeight)
            {
                moveStepY = -moveStepY;
                moveStepX = -moveStepX;
                score++;
            }

            // วาดฟอร์มใหม่ขึ้นมา
            this.Invalidate();
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {

            // เงื่อนไขในการตรวจสอบการกดปุ่ม ESC
            if (e.KeyCode == Keys.Escape)
            {
                Application.Exit(); // ออกจากแอปพลิเคชั้น
                return; // ส่งค่ากลับเพื่อจบการทำงานโปรแกรม
            }

            // เงื่อนไขการควบคุมการเคลื่อนไหวของแป้นโดยใช้ปุ่มลูกศรซ้าย และปุ่มลูกศรขวา สำหรับการเคลื่อนที่ซ้ายและขวา
            if (e.KeyCode == Keys.Left)
            {
                isLeftPressed = true;
                paddleTimer.Start();
            }
            else if (e.KeyCode == Keys.Right)
            {
                isRightPressed = true;
                paddleTimer.Start();
            }

            // เงื่อนไขการควบคุมการเคลื่อนไหวของแป้นโดยใช้ปุ่มลูกศรบน และปุ่มลูกศรล่าง สำหรับการเคลื่อนที่บนและล่าง
            if (e.KeyCode == Keys.Up)
            {
                isUpPressed = true;
                paddleTimer.Start();
            }
            else if (e.KeyCode == Keys.Down)
            {
                isDownPressed = true;
                paddleTimer.Start();
            }
            else if (e.KeyCode == Keys.Q)
            {
                //สุ่มตำแหน่งการเกิดของลูกบอล
                int ranposition = ran.Next(1, 4);

                // กำหนดตำแหน่งลูกบอลตอนเริ่มต้น


                ballPosX = (this.ClientSize.Width - ballWidth) / ranposition; // [ค่ามาตรฐาน : 2] กำหนดตำแหน่งในแนวนอนของลูกบอล
                ballPosY = (this.ClientSize.Height - ballHeight) / ranposition; // [ค่ามาตรฐาน : 2] กำหนดตำแหน่งในแนวตั้งของลูกบอล

            }
            else if (e.KeyCode == Keys.W)
            {
                //สุ่มตำแหน่งการเกิดของลูกบอล
                int ranposition = ran.Next(1, 4);

                // กำหนดตำแหน่งแป้นตอนเริ่มต้น
                paddlePosX = (this.ClientSize.Width - paddleWidth) / ranposition; // [ค่ามาตรฐาน : 1] กำหนดตำแหน่งในแนวนอนของแป้น
                paddlePosY = this.ClientSize.Height - paddleHeight + ranposition; // [ค่ามาตรฐาน : 500] กำหนดตำแหน่งในแนวตั้งของแป้น

            }
            else if (e.KeyCode == Keys.E)
            {       
                score = 0;
            }
            else if (e.KeyCode == Keys.R)
            {
                //สุ่มตำแหน่งการเกิดของลูกบอล
                float BallRanposition = ran.Next(1, 4);

                // กำหนดตำแหน่งลูกบอลตอนเริ่มต้น
                ballPosX = (this.ClientSize.Width - ballWidth) / BallRanposition; // [ค่ามาตรฐาน : 2] กำหนดตำแหน่งในแนวนอนของลูกบอล
                ballPosY = (this.ClientSize.Height - ballHeight) / BallRanposition; // [ค่ามาตรฐาน : 2] กำหนดตำแหน่งในแนวตั้งของลูกบอล

                score = 0;
            }


        }

        private void OnKeyUp(object sender, KeyEventArgs e)
        {
 
            // เงื่อนไขในการตรวจสอบว่าให้แป้นหยุดเคลื่อนไหว ถ้าหากปล่อยปุ่มกดของลูกศร
            if (e.KeyCode == Keys.Left)
            {
                isLeftPressed = false;
                if (!isRightPressed)
                {
                    paddleTimer.Stop();
                }
            }
            else if (e.KeyCode == Keys.Right)
            {
                isRightPressed = false;
                if (!isLeftPressed)
                {
                    paddleTimer.Stop();
                }
            }
            else if (e.KeyCode == Keys.Up)
            {
                isUpPressed = false;
                if (!isDownPressed)
                {
                    paddleTimer.Stop();
                }
            }
            else if (e.KeyCode == Keys.Down)
            {
                isDownPressed = false;
                if (!isUpPressed)
                {
                    paddleTimer.Stop();
                }
            }
            
        }

        private void MovePaddle(object sender, EventArgs e)
        {

            // อัปเดตตำแหน่งของลูกบอลเมื่อกดปุ่มลูกศรซ้าย และปุ่มลูกศรขวา สำหรับการเคลื่อนที่ซ้ายและขวา
            if (isLeftPressed && paddlePosX > 0)
            {
                paddlePosX -= paddleMoveStep;
            }
            else if (isRightPressed && paddlePosX + paddleWidth < this.ClientSize.Width)
            {
                paddlePosX += paddleMoveStep;
            }

            // อัปเดตตำแหน่งของลูกบอลเมื่อกดปุ่มลูกศรบน และปุ่มลูกศรล่าง สำหรับการเคลื่อนที่บนและล่าง
            if (isUpPressed && paddlePosY > 0)
            {
                paddlePosY -= paddleMoveStep;
            }
            else if (isDownPressed && paddlePosY + paddleWidth < this.ClientSize.Width)
            {
                paddlePosY += paddleMoveStep;
            }

            // วาดฟอร์มใหม่ขึ้นมา
            this.Invalidate();

        }

        private void Form1_Load(object sender, EventArgs e)
        {

            // ตั้งค่าให้หน้าฟอร์มเป็นแบบเต็มหน้าจอ [full screen]
            this.FormBorderStyle = FormBorderStyle.None; // ลบขอบของหน้าจอ
            this.WindowState = FormWindowState.Maximized; // กำหนดหน้าจอของฟอร์มให้ใหญ่สุด

        }

        private void RespondBall(object sender, EventArgs e)
        {
 

        }

    }

}