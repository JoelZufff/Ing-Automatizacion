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
            this.SerialPort = new System.IO.Ports.SerialPort(this.components);
            this.Control_Panel = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.RX_text = new System.Windows.Forms.Label();
            this.Theta_dir = new System.Windows.Forms.CheckBox();
            this.Z_dir = new System.Windows.Forms.CheckBox();
            this.X_dir = new System.Windows.Forms.CheckBox();
            this.Send = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.Theta_number = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.Z_number = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.X_number = new System.Windows.Forms.NumericUpDown();
            this.Title_Theta = new System.Windows.Forms.Label();
            this.Title_Z = new System.Windows.Forms.Label();
            this.Title_X = new System.Windows.Forms.Label();
            this.Temp2 = new System.Windows.Forms.Label();
            this.Temp1 = new System.Windows.Forms.Label();
            this.ConectionTimer = new System.Windows.Forms.Timer(this.components);
            this.ConectionPanel = new System.Windows.Forms.Panel();
            this.ConectionButton = new System.Windows.Forms.Button();
            this.ConectionProgressBar = new System.Windows.Forms.ProgressBar();
            this.ConectionTitle = new System.Windows.Forms.Label();
            this.Control_Panel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Theta_number)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Z_number)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.X_number)).BeginInit();
            this.ConectionPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // SerialPort
            // 
            this.SerialPort.BaudRate = 115200;
            this.SerialPort.PortName = "COM3";
            this.SerialPort.ReadTimeout = 500;
            this.SerialPort.WriteTimeout = 500;
            this.SerialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort_DataReceived);
            // 
            // Control_Panel
            // 
            this.Control_Panel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.Control_Panel.Controls.Add(this.button1);
            this.Control_Panel.Controls.Add(this.RX_text);
            this.Control_Panel.Controls.Add(this.Theta_dir);
            this.Control_Panel.Controls.Add(this.Z_dir);
            this.Control_Panel.Controls.Add(this.X_dir);
            this.Control_Panel.Controls.Add(this.Send);
            this.Control_Panel.Controls.Add(this.label3);
            this.Control_Panel.Controls.Add(this.Theta_number);
            this.Control_Panel.Controls.Add(this.label2);
            this.Control_Panel.Controls.Add(this.Z_number);
            this.Control_Panel.Controls.Add(this.label1);
            this.Control_Panel.Controls.Add(this.X_number);
            this.Control_Panel.Controls.Add(this.Title_Theta);
            this.Control_Panel.Controls.Add(this.Title_Z);
            this.Control_Panel.Controls.Add(this.Title_X);
            this.Control_Panel.Controls.Add(this.Temp2);
            this.Control_Panel.Controls.Add(this.Temp1);
            this.Control_Panel.Location = new System.Drawing.Point(2, 9);
            this.Control_Panel.Name = "Control_Panel";
            this.Control_Panel.Size = new System.Drawing.Size(640, 464);
            this.Control_Panel.TabIndex = 14;
            this.Control_Panel.Visible = false;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(514, 405);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 22;
            this.button1.Text = "Actualizar";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // RX_text
            // 
            this.RX_text.AutoSize = true;
            this.RX_text.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.RX_text.Location = new System.Drawing.Point(48, 410);
            this.RX_text.Name = "RX_text";
            this.RX_text.Size = new System.Drawing.Size(35, 13);
            this.RX_text.TabIndex = 21;
            this.RX_text.Text = "label4";
            // 
            // Theta_dir
            // 
            this.Theta_dir.AutoSize = true;
            this.Theta_dir.Checked = true;
            this.Theta_dir.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Theta_dir.ForeColor = System.Drawing.Color.White;
            this.Theta_dir.Location = new System.Drawing.Point(500, 143);
            this.Theta_dir.Name = "Theta_dir";
            this.Theta_dir.Size = new System.Drawing.Size(76, 17);
            this.Theta_dir.TabIndex = 20;
            this.Theta_dir.Text = "Antihorario";
            this.Theta_dir.UseVisualStyleBackColor = true;
            // 
            // Z_dir
            // 
            this.Z_dir.AutoSize = true;
            this.Z_dir.Checked = true;
            this.Z_dir.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Z_dir.ForeColor = System.Drawing.Color.White;
            this.Z_dir.Location = new System.Drawing.Point(288, 143);
            this.Z_dir.Name = "Z_dir";
            this.Z_dir.Size = new System.Drawing.Size(53, 17);
            this.Z_dir.TabIndex = 19;
            this.Z_dir.Text = "Arriba";
            this.Z_dir.UseVisualStyleBackColor = true;
            // 
            // X_dir
            // 
            this.X_dir.AutoSize = true;
            this.X_dir.Checked = true;
            this.X_dir.CheckState = System.Windows.Forms.CheckState.Checked;
            this.X_dir.ForeColor = System.Drawing.Color.White;
            this.X_dir.Location = new System.Drawing.Point(76, 143);
            this.X_dir.Name = "X_dir";
            this.X_dir.Size = new System.Drawing.Size(67, 17);
            this.X_dir.TabIndex = 18;
            this.X_dir.Text = "Derecha";
            this.X_dir.UseVisualStyleBackColor = true;
            // 
            // Send
            // 
            this.Send.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Send.Location = new System.Drawing.Point(243, 353);
            this.Send.Name = "Send";
            this.Send.Size = new System.Drawing.Size(140, 41);
            this.Send.TabIndex = 14;
            this.Send.Text = "Enviar";
            this.Send.UseVisualStyleBackColor = true;
            this.Send.Click += new System.EventHandler(this.Send_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.label3.Location = new System.Drawing.Point(499, 219);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(68, 24);
            this.label3.TabIndex = 13;
            this.label3.Text = "grados";
            // 
            // Theta_number
            // 
            this.Theta_number.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Theta_number.Location = new System.Drawing.Point(473, 177);
            this.Theta_number.Maximum = new decimal(new int[] {
            360,
            0,
            0,
            0});
            this.Theta_number.Name = "Theta_number";
            this.Theta_number.Size = new System.Drawing.Size(116, 29);
            this.Theta_number.TabIndex = 12;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.label2.Location = new System.Drawing.Point(305, 219);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 24);
            this.label2.TabIndex = 11;
            this.label2.Text = "cm";
            // 
            // Z_number
            // 
            this.Z_number.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Z_number.Location = new System.Drawing.Point(267, 177);
            this.Z_number.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.Z_number.Name = "Z_number";
            this.Z_number.Size = new System.Drawing.Size(116, 29);
            this.Z_number.TabIndex = 10;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.label1.Location = new System.Drawing.Point(91, 219);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 24);
            this.label1.TabIndex = 9;
            this.label1.Text = "cm";
            // 
            // X_number
            // 
            this.X_number.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.X_number.Location = new System.Drawing.Point(51, 177);
            this.X_number.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.X_number.Name = "X_number";
            this.X_number.Size = new System.Drawing.Size(116, 29);
            this.X_number.TabIndex = 8;
            // 
            // Title_Theta
            // 
            this.Title_Theta.AutoSize = true;
            this.Title_Theta.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Title_Theta.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.Title_Theta.Location = new System.Drawing.Point(467, 68);
            this.Title_Theta.Name = "Title_Theta";
            this.Title_Theta.Size = new System.Drawing.Size(139, 33);
            this.Title_Theta.TabIndex = 7;
            this.Title_Theta.Text = "Eje Theta";
            // 
            // Title_Z
            // 
            this.Title_Z.AutoSize = true;
            this.Title_Z.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Title_Z.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.Title_Z.Location = new System.Drawing.Point(282, 68);
            this.Title_Z.Name = "Title_Z";
            this.Title_Z.Size = new System.Drawing.Size(83, 33);
            this.Title_Z.TabIndex = 6;
            this.Title_Z.Text = "Eje Z";
            // 
            // Title_X
            // 
            this.Title_X.AutoSize = true;
            this.Title_X.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Title_X.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.Title_X.Location = new System.Drawing.Point(70, 68);
            this.Title_X.Name = "Title_X";
            this.Title_X.Size = new System.Drawing.Size(84, 33);
            this.Title_X.TabIndex = 5;
            this.Title_X.Text = "Eje X";
            // 
            // Temp2
            // 
            this.Temp2.AutoSize = true;
            this.Temp2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Temp2.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.Temp2.Location = new System.Drawing.Point(492, 291);
            this.Temp2.Name = "Temp2";
            this.Temp2.Size = new System.Drawing.Size(69, 24);
            this.Temp2.TabIndex = 1;
            this.Temp2.Text = "2.00 °C";
            // 
            // Temp1
            // 
            this.Temp1.AutoSize = true;
            this.Temp1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Temp1.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.Temp1.Location = new System.Drawing.Point(85, 296);
            this.Temp1.Name = "Temp1";
            this.Temp1.Size = new System.Drawing.Size(69, 24);
            this.Temp1.TabIndex = 0;
            this.Temp1.Text = "1.00 °C";
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
            this.ConectionPanel.Size = new System.Drawing.Size(643, 464);
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
            this.ClientSize = new System.Drawing.Size(639, 461);
            this.Controls.Add(this.Control_Panel);
            this.Controls.Add(this.ConectionPanel);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MinimumSize = new System.Drawing.Size(655, 500);
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Grua de 3 ejes";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Main_FormClosed);
            this.Load += new System.EventHandler(this.Main_Load);
            this.Control_Panel.ResumeLayout(false);
            this.Control_Panel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Theta_number)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Z_number)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.X_number)).EndInit();
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
        public System.Windows.Forms.Label Title_X;
        public System.Windows.Forms.Label Title_Theta;
        public System.Windows.Forms.Label Title_Z;
        public System.Windows.Forms.NumericUpDown X_number;
        public System.Windows.Forms.Label label1;
        public System.Windows.Forms.Label label3;
        public System.Windows.Forms.NumericUpDown Theta_number;
        public System.Windows.Forms.Label label2;
        public System.Windows.Forms.NumericUpDown Z_number;
        public System.Windows.Forms.Button Send;
        public System.Windows.Forms.Label Temp2;
        public System.Windows.Forms.Label Temp1;
        private System.Windows.Forms.CheckBox Theta_dir;
        private System.Windows.Forms.CheckBox Z_dir;
        private System.Windows.Forms.CheckBox X_dir;
        private System.Windows.Forms.Label RX_text;
        private System.Windows.Forms.Button button1;
    }
}

