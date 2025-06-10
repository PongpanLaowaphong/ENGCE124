using System;
using System.Drawing;
using System.Windows.Forms;

namespace Bouncing_ball
{
    public partial class Form1 : Form
    {

        //��˹�����õ�ҧ������ҹ������

        private int ballWidth = 40; // �������ҧ�ͧ�١��� ��˹����� �ԡ��
        private int ballHeight = 40; // �����٧�ͧ�١��� ��˹����� �ԡ��
        private float ballPosX = 0; // ���˹��١��ź�᡹ X
        private float ballPosY = 0; // ���˹��١��ź�᡹ Y
        private float moveStepX = 8; // [����ҵðҹ : 4] �������ǡ������͹�ͧ�١��ź�᡹ X ��˹����� �ԡ��
        private int moveStepY = 8; // [����ҵðҹ : 4] �������ǡ������͹�ͧ�١��ź�᡹ Y ��˹����� �ԡ��
        private System.Windows.Forms.Timer ballTimer; // �Ѻ��������Ѻ�Ҿ����͹��Ǣͧ�١���

        private int paddleWidth = 300; // �������ҧ�ͧ�� ��˹����� �ԡ��
        private int paddleHeight = 5; // �����٧�ͧ�� ��˹����� �ԡ��
        private int paddlePosX; // ���˹��鹺�᡹ X
        private int paddlePosY; // ���˹��鹺�᡹ Y
        private int paddleMoveStep = 32; // [����ҵðҹ : 8] �������ǡ������͹�ͧ�� ��˹����� �ԡ��
        private System.Windows.Forms.Timer paddleTimer; // �Ѻ��������Ѻ�Ҿ����͹��Ǣͧ��

        private bool isLeftPressed = false; // �Դ�����ҡ������١�ë��¶١��
        private bool isRightPressed = false; // �Դ�����ҡ������١�â�Ҷ١��

        private bool isUpPressed = false; // �Դ�����ҡ������١�ú��١��
        private bool isDownPressed = false; // �Դ�����ҡ������١����ҧ�١��

        Random ran = new Random(); // ����Ѻ����������˹觡���Դ�ͧ�١���������

        int score = 0;


        public Form1()
        {
            InitializeComponent();

            // ��ҹ�ѧ��ѹ����ժ������ Form1_Load
            this.Load += new EventHandler(Form1_Load);

            // ��駤�Һѿ�����ͧ�������Ŵ��������� [�����͹䢹����������١�������͹����դ���������]
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer | ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint, true);
            this.UpdateStyles();

            // ������鹨Ѻ�����١��� ��������͹���
            // ��èѺ���Ҩз�����Դ����ѻവ���˹觢ͧ�١���������� �����ǧ���ҷ���˹�
            ballTimer = new System.Windows.Forms.Timer();
            ballTimer.Interval = 30; // ��駤�Ҫ�ǧ���� ��˹����� ������Թҷ�
            ballTimer.Tick += new EventHandler(MoveBall); //�����ҹ�ѧ��ѹ Moveball ����ռšѺ��èѺ����
            ballTimer.Start(); //������鹡�èѺ����

            // ������鹨Ѻ������ ��������͹���
            // ��èѺ���Ҩз�����Դ����ѻവ���˹觢ͧ�١���������� �����ǧ���ҷ���˹�
            paddleTimer = new System.Windows.Forms.Timer();
            paddleTimer.Interval = 15; // ��駤�Ҫ�ǧ���� ��˹����� ������Թҷ�
            paddleTimer.Tick += new EventHandler(MovePaddle); //�����ҹ�ѧ��ѹ Movepaddle ����ռšѺ��èѺ����


            //�������˹觡���Դ�ͧ�١���
            float BallRanposition = ran.Next(1,4);
            int PaddleRanposition = ran.Next(1,4);

            // ��˹����˹��١��ŵ͹�������
    
            ballPosX = (this.ClientSize.Width - ballWidth) / BallRanposition; // [����ҵðҹ : 2] ��˹����˹���ǹ͹�ͧ�١���
            ballPosY = (this.ClientSize.Height - ballHeight) / BallRanposition; // [����ҵðҹ : 2] ��˹����˹���ǵ�駢ͧ�١���

            // ��˹����˹��鹵͹�������
            paddlePosX = (this.ClientSize.Width - paddleWidth) / PaddleRanposition; // [����ҵðҹ : 1] ��˹����˹���ǹ͹�ͧ��
            paddlePosY = this.ClientSize.Height - paddleHeight + PaddleRanposition; // [����ҵðҹ : 500] ��˹����˹���ǵ�駢ͧ��

            // ��ҹ�ѧ��ѹ Paintcircle
            this.Paint += new PaintEventHandler(PaintCircle);

            // ��ҹ�ѧ��ѹ OnKeyDown ��� �ѧ��ѹ OnKeyDown
            this.KeyDown += new KeyEventHandler(OnKeyDown);
            this.KeyUp += new KeyEventHandler(OnKeyUp);

        }

        private void PaintCircle(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias; // ������ͺ�ͧ�١������º���

            e.Graphics.Clear(this.BackColor); // ��ҧ��鹷���Ҵ�����վ����ѧ�ͧ�����

            // ���¡��ҹ���ʹ�ͧ����Ҵ�ٻ�١���
            PaintBall(e.Graphics);

            // ���¡��ҹ���ʹ�ͧ����Ҵ�ٻ��
            PaintPaddle(e.Graphics);

            // ���¡��ҹ���ʹ�ͧ����Ҵ�ٻ ��¹���ͼ���
            PongpanLaowaphong(e.Graphics);

        }

        private void PaintBall(Graphics graphics)
        {
            // �Ҵ�١��Ţ�����������ᴧ
            graphics.FillEllipse(Brushes.Red, ballPosX, ballPosY, ballWidth, ballHeight);

            // ����ͺ�մ����Ѻ�١���
            graphics.DrawEllipse(Pens.Black, ballPosX, ballPosY, ballWidth, ballHeight);

        }

        private void PongpanLaowaphong(Graphics graphics)
        {

            // ��¹��ͤ��� "Pongpan Laowaphong [66543206019-2]"
            string message = $"Pongpan Laowaphong [66543206019-2] \nScore from hit the paddle : {score}";
            Font font = new Font("Arial", 24, FontStyle.Bold);
            SizeF textSize = graphics.MeasureString(message, font);

            // ��˹����˹����Ѻ���˹ѧ��� (��˹������º�)
            float x = (this.ClientSize.Width - textSize.Width) / 40;
            float y = (this.ClientSize.Height - textSize.Height) / 25;

            graphics.DrawString(message, font, Brushes.Black, x, y);

        }

        private void PaintPaddle(Graphics graphics)
        {
            // �Ҵ�鹢����������չ���Թ
            graphics.FillRectangle(Brushes.Blue, paddlePosX, paddlePosY, paddleWidth, paddleHeight);
        }
        private void MoveBall(object sender, EventArgs e)
        {
            
            // �ѻവ���˹觢ͧ�١���
            ballPosX += moveStepX;
            ballPosY += moveStepY;

            // ��Ǩ�ͺ��ê��ͧ�ѵ�ءѺ�ͺ˹�Ҩ� ����з�͹�Ѻ�㹷�ȷҧ�ç�ѹ����
            if (ballPosX < 0 || ballPosX + ballWidth > this.ClientSize.Width)
            {
                moveStepX = -moveStepX;
            }

            if (ballPosY < 0 || ballPosY + ballHeight > this.ClientSize.Height)
            {
                moveStepY = -moveStepY;

            }

            //  ��Ǩ�ͺ��ê��ͧ�ѵ�ءѺ�� ����з�͹�Ѻ�㹷�ȷҧ�ç�ѹ����
            if (ballPosX + ballWidth > paddlePosX && ballPosX < paddlePosX + paddleWidth &&
                ballPosY + ballHeight > paddlePosY && ballPosY < paddlePosY + paddleHeight)
            {
                moveStepY = -moveStepY;
                moveStepX = -moveStepX;
                score++;
            }

            // �Ҵ�������������
            this.Invalidate();
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {

            // ���͹�㹡�õ�Ǩ�ͺ��á����� ESC
            if (e.KeyCode == Keys.Escape)
            {
                Application.Exit(); // �͡�ҡ�ͻ���प��
                return; // �觤�ҡ�Ѻ���ͨ���÷ӧҹ�����
            }

            // ���͹䢡�äǺ����������͹��Ǣͧ����������١�ë��� ��л����١�â�� ����Ѻ�������͹��������Т��
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

            // ���͹䢡�äǺ����������͹��Ǣͧ����������١�ú� ��л����١����ҧ ����Ѻ�������͹��躹�����ҧ
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
                //�������˹觡���Դ�ͧ�١���
                int ranposition = ran.Next(1, 4);

                // ��˹����˹��١��ŵ͹�������


                ballPosX = (this.ClientSize.Width - ballWidth) / ranposition; // [����ҵðҹ : 2] ��˹����˹���ǹ͹�ͧ�١���
                ballPosY = (this.ClientSize.Height - ballHeight) / ranposition; // [����ҵðҹ : 2] ��˹����˹���ǵ�駢ͧ�١���

            }
            else if (e.KeyCode == Keys.W)
            {
                //�������˹觡���Դ�ͧ�١���
                int ranposition = ran.Next(1, 4);

                // ��˹����˹��鹵͹�������
                paddlePosX = (this.ClientSize.Width - paddleWidth) / ranposition; // [����ҵðҹ : 1] ��˹����˹���ǹ͹�ͧ��
                paddlePosY = this.ClientSize.Height - paddleHeight + ranposition; // [����ҵðҹ : 500] ��˹����˹���ǵ�駢ͧ��

            }
            else if (e.KeyCode == Keys.E)
            {       
                score = 0;
            }
            else if (e.KeyCode == Keys.R)
            {
                //�������˹觡���Դ�ͧ�١���
                float BallRanposition = ran.Next(1, 4);

                // ��˹����˹��١��ŵ͹�������
                ballPosX = (this.ClientSize.Width - ballWidth) / BallRanposition; // [����ҵðҹ : 2] ��˹����˹���ǹ͹�ͧ�١���
                ballPosY = (this.ClientSize.Height - ballHeight) / BallRanposition; // [����ҵðҹ : 2] ��˹����˹���ǵ�駢ͧ�١���

                score = 0;
            }


        }

        private void OnKeyUp(object sender, KeyEventArgs e)
        {
 
            // ���͹�㹡�õ�Ǩ�ͺ����������ش����͹��� ����ҡ����»������ͧ�١��
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

            // �ѻവ���˹觢ͧ�١�������͡������١�ë��� ��л����١�â�� ����Ѻ�������͹��������Т��
            if (isLeftPressed && paddlePosX > 0)
            {
                paddlePosX -= paddleMoveStep;
            }
            else if (isRightPressed && paddlePosX + paddleWidth < this.ClientSize.Width)
            {
                paddlePosX += paddleMoveStep;
            }

            // �ѻവ���˹觢ͧ�١�������͡������١�ú� ��л����١����ҧ ����Ѻ�������͹��躹�����ҧ
            if (isUpPressed && paddlePosY > 0)
            {
                paddlePosY -= paddleMoveStep;
            }
            else if (isDownPressed && paddlePosY + paddleWidth < this.ClientSize.Width)
            {
                paddlePosY += paddleMoveStep;
            }

            // �Ҵ�������������
            this.Invalidate();

        }

        private void Form1_Load(object sender, EventArgs e)
        {

            // ��駤�����˹�ҿ������Ẻ���˹�Ҩ� [full screen]
            this.FormBorderStyle = FormBorderStyle.None; // ź�ͺ�ͧ˹�Ҩ�
            this.WindowState = FormWindowState.Maximized; // ��˹�˹�Ҩͧ͢���������˭��ش

        }

        private void RespondBall(object sender, EventArgs e)
        {
 

        }

    }

}