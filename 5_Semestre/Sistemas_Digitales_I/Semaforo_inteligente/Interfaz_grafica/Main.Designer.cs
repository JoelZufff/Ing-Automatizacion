namespace Wire_Trimmer
{
    partial class Main
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.Timer Act_variables;
            this.SerialPort = new System.IO.Ports.SerialPort(this.components);
            this.Control_Panel = new System.Windows.Forms.Panel();
            this.PTL = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.WE = new System.Windows.Forms.NumericUpDown();
            this.EW = new System.Windows.Forms.NumericUpDown();
            this.SN = new System.Windows.Forms.NumericUpDown();
            this.NS = new System.Windows.Forms.NumericUpDown();
            this.TEMP_num = new System.Windows.Forms.NumericUpDown();
            this.TEMP_title = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.ConectionTimer = new System.Windows.Forms.Timer(this.components);
            this.ConectionPanel = new System.Windows.Forms.Panel();
            this.ConectionButton = new System.Windows.Forms.Button();
            this.ConectionProgressBar = new System.Windows.Forms.ProgressBar();
            this.ConectionTitle = new System.Windows.Forms.Label();
            Act_variables = new System.Windows.Forms.Timer(this.components);
            this.Control_Panel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PTL)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.WE)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.EW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SN)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.NS)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TEMP_num)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.ConectionPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // Act_variables
            // 
            Act_variables.Enabled = true;
            Act_variables.Tick += new System.EventHandler(this.Act_variables_Tick);
            // 
            // SerialPort
            // 
            this.SerialPort.PortName = "COM3";
            this.SerialPort.ReadTimeout = 500;
            this.SerialPort.WriteTimeout = 500;
            this.SerialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort_DataReceived);
            // 
            // Control_Panel
            // 
            this.Control_Panel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.Control_Panel.Controls.Add(this.PTL);
            this.Control_Panel.Controls.Add(this.label1);
            this.Control_Panel.Controls.Add(this.WE);
            this.Control_Panel.Controls.Add(this.EW);
            this.Control_Panel.Controls.Add(this.SN);
            this.Control_Panel.Controls.Add(this.NS);
            this.Control_Panel.Controls.Add(this.TEMP_num);
            this.Control_Panel.Controls.Add(this.TEMP_title);
            this.Control_Panel.Controls.Add(this.pictureBox1);
            this.Control_Panel.Location = new System.Drawing.Point(2, 9);
            this.Control_Panel.Name = "Control_Panel";
            this.Control_Panel.Size = new System.Drawing.Size(640, 567);
            this.Control_Panel.TabIndex = 14;
            this.Control_Panel.Visible = false;
            // 
            // PTL
            // 
            this.PTL.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.PTL.Enabled = false;
            this.PTL.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PTL.Location = new System.Drawing.Point(339, 517);
            this.PTL.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.PTL.Name = "PTL";
            this.PTL.ReadOnly = true;
            this.PTL.Size = new System.Drawing.Size(120, 35);
            this.PTL.TabIndex = 9;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(149, 523);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(162, 24);
            this.label1.TabIndex = 8;
            this.label1.Text = "Distancia peatonal";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // WE
            // 
            this.WE.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.WE.Enabled = false;
            this.WE.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.WE.Location = new System.Drawing.Point(15, 252);
            this.WE.Maximum = new decimal(new int[] {
            99,
            0,
            0,
            0});
            this.WE.Name = "WE";
            this.WE.ReadOnly = true;
            this.WE.Size = new System.Drawing.Size(120, 35);
            this.WE.TabIndex = 7;
            // 
            // EW
            // 
            this.EW.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.EW.Enabled = false;
            this.EW.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EW.Location = new System.Drawing.Point(505, 252);
            this.EW.Maximum = new decimal(new int[] {
            99,
            0,
            0,
            0});
            this.EW.Name = "EW";
            this.EW.ReadOnly = true;
            this.EW.Size = new System.Drawing.Size(120, 35);
            this.EW.TabIndex = 6;
            // 
            // SN
            // 
            this.SN.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.SN.Enabled = false;
            this.SN.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SN.Location = new System.Drawing.Point(265, 455);
            this.SN.Maximum = new decimal(new int[] {
            99,
            0,
            0,
            0});
            this.SN.Name = "SN";
            this.SN.ReadOnly = true;
            this.SN.Size = new System.Drawing.Size(120, 35);
            this.SN.TabIndex = 5;
            // 
            // NS
            // 
            this.NS.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.NS.Enabled = false;
            this.NS.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NS.Location = new System.Drawing.Point(265, 59);
            this.NS.Maximum = new decimal(new int[] {
            99,
            0,
            0,
            0});
            this.NS.Name = "NS";
            this.NS.ReadOnly = true;
            this.NS.Size = new System.Drawing.Size(120, 35);
            this.NS.TabIndex = 4;
            // 
            // TEMP_num
            // 
            this.TEMP_num.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.TEMP_num.Enabled = false;
            this.TEMP_num.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TEMP_num.Location = new System.Drawing.Point(376, 3);
            this.TEMP_num.Maximum = new decimal(new int[] {
            99,
            0,
            0,
            0});
            this.TEMP_num.Name = "TEMP_num";
            this.TEMP_num.ReadOnly = true;
            this.TEMP_num.Size = new System.Drawing.Size(120, 35);
            this.TEMP_num.TabIndex = 1;
            // 
            // TEMP_title
            // 
            this.TEMP_title.AutoSize = true;
            this.TEMP_title.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TEMP_title.ForeColor = System.Drawing.Color.White;
            this.TEMP_title.Location = new System.Drawing.Point(119, 8);
            this.TEMP_title.Name = "TEMP_title";
            this.TEMP_title.Size = new System.Drawing.Size(201, 24);
            this.TEMP_title.TabIndex = 0;
            this.TEMP_title.Text = "Temperatura ambiente";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::Wire_Trimmer.Properties.Resources.Interseccion;
            this.pictureBox1.Location = new System.Drawing.Point(164, 113);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(317, 321);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            // 
            // ConectionTimer
            // 
            this.ConectionTimer.Interval = 5000;
            this.ConectionTimer.Tick += new System.EventHandler(this.ConectionTimer_Tick);
            // 
            // ConectionPanel
            // 
            this.ConectionPanel.Controls.Add(this.ConectionButton);
            this.ConectionPanel.Controls.Add(this.ConectionProgressBar);
            this.ConectionPanel.Controls.Add(this.ConectionTitle);
            this.ConectionPanel.Location = new System.Drawing.Point(2, 12);
            this.ConectionPanel.Name = "ConectionPanel";
            this.ConectionPanel.Size = new System.Drawing.Size(643, 447);
            this.ConectionPanel.TabIndex = 15;
            // 
            // ConectionButton
            // 
            this.ConectionButton.Location = new System.Drawing.Point(232, 323);
            this.ConectionButton.Name = "ConectionButton";
            this.ConectionButton.Size = new System.Drawing.Size(173, 39);
            this.ConectionButton.TabIndex = 3;
            this.ConectionButton.Text = "Conectar";
            this.ConectionButton.UseVisualStyleBackColor = true;
            this.ConectionButton.Click += new System.EventHandler(this.ConectionButton_Click);
            // 
            // ConectionProgressBar
            // 
            this.ConectionProgressBar.Location = new System.Drawing.Point(141, 226);
            this.ConectionProgressBar.Name = "ConectionProgressBar";
            this.ConectionProgressBar.Size = new System.Drawing.Size(340, 49);
            this.ConectionProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.ConectionProgressBar.TabIndex = 2;
            // 
            // ConectionTitle
            // 
            this.ConectionTitle.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ConectionTitle.AutoSize = true;
            this.ConectionTitle.Font = new System.Drawing.Font("Corbel", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ConectionTitle.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ConectionTitle.Location = new System.Drawing.Point(224, 127);
            this.ConectionTitle.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.ConectionTitle.Name = "ConectionTitle";
            this.ConectionTitle.Size = new System.Drawing.Size(171, 45);
            this.ConectionTitle.TabIndex = 1;
            this.ConectionTitle.Text = "Conexion";
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(639, 581);
            this.Controls.Add(this.Control_Panel);
            this.Controls.Add(this.ConectionPanel);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MinimumSize = new System.Drawing.Size(655, 620);
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Semaforo inteligente";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Main_FormClosed);
            this.Load += new System.EventHandler(this.Main_Load);
            this.Control_Panel.ResumeLayout(false);
            this.Control_Panel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PTL)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.WE)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.EW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SN)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.NS)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TEMP_num)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ConectionPanel.ResumeLayout(false);
            this.ConectionPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        public System.IO.Ports.SerialPort SerialPort;
        public System.Windows.Forms.Panel Control_Panel;
        public System.Windows.Forms.Timer ConectionTimer;
        public System.Windows.Forms.Panel ConectionPanel;
        public System.Windows.Forms.Button ConectionButton;
        public System.Windows.Forms.ProgressBar ConectionProgressBar;
        public System.Windows.Forms.Label ConectionTitle;
        private System.Windows.Forms.Label TEMP_title;
        private System.Windows.Forms.NumericUpDown TEMP_num;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.NumericUpDown NS;
        private System.Windows.Forms.NumericUpDown SN;
        private System.Windows.Forms.NumericUpDown WE;
        private System.Windows.Forms.NumericUpDown EW;
        private System.Windows.Forms.NumericUpDown PTL;
        private System.Windows.Forms.Label label1;
    }
}

