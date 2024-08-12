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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.Title = new System.Windows.Forms.Label();
            this.PrintButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.OrderDataGridView = new System.Windows.Forms.DataGridView();
            this.AddButton = new System.Windows.Forms.Button();
            this.EraseButton = new System.Windows.Forms.Button();
            this.SerialPort = new System.IO.Ports.SerialPort(this.components);
            this.WireOrderPanel = new System.Windows.Forms.Panel();
            this.ReelLabel = new System.Windows.Forms.Label();
            this.PeelingLength = new System.Windows.Forms.NumericUpDown();
            this.Length = new System.Windows.Forms.NumericUpDown();
            this.Amount = new System.Windows.Forms.NumericUpDown();
            this.ConectionTimer = new System.Windows.Forms.Timer(this.components);
            this.ConectionPanel = new System.Windows.Forms.Panel();
            this.ConectionButton = new System.Windows.Forms.Button();
            this.ConectionProgressBar = new System.Windows.Forms.ProgressBar();
            this.ConectionTitle = new System.Windows.Forms.Label();
            this.OrderTimer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.OrderDataGridView)).BeginInit();
            this.WireOrderPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PeelingLength)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Length)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Amount)).BeginInit();
            this.ConectionPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // Title
            // 
            this.Title.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Title.AutoSize = true;
            this.Title.Font = new System.Drawing.Font("Corbel", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Title.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.Title.Location = new System.Drawing.Point(117, 15);
            this.Title.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.Title.Name = "Title";
            this.Title.Size = new System.Drawing.Size(327, 36);
            this.Title.TabIndex = 0;
            this.Title.Text = "Carrete Disponible (mm):";
            // 
            // PrintButton
            // 
            this.PrintButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PrintButton.Enabled = false;
            this.PrintButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PrintButton.Location = new System.Drawing.Point(283, 504);
            this.PrintButton.Margin = new System.Windows.Forms.Padding(2);
            this.PrintButton.Name = "PrintButton";
            this.PrintButton.Size = new System.Drawing.Size(145, 49);
            this.PrintButton.TabIndex = 1;
            this.PrintButton.Text = "Imprimir";
            this.PrintButton.UseVisualStyleBackColor = true;
            this.PrintButton.Click += new System.EventHandler(this.PrintButton_Click);
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label2.Location = new System.Drawing.Point(301, 75);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(145, 20);
            this.label2.TabIndex = 6;
            this.label2.Text = "Cantidad de cables";
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label3.Location = new System.Drawing.Point(40, 75);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(111, 20);
            this.label3.TabIndex = 7;
            this.label3.Text = "Longitud (mm)";
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label4.Location = new System.Drawing.Point(183, 75);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(98, 20);
            this.label4.TabIndex = 8;
            this.label4.Text = "Pelado (mm)";
            // 
            // OrderDataGridView
            // 
            this.OrderDataGridView.AllowUserToAddRows = false;
            this.OrderDataGridView.AllowUserToDeleteRows = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.OrderDataGridView.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
            this.OrderDataGridView.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.OrderDataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.OrderDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.OrderDataGridView.Location = new System.Drawing.Point(38, 150);
            this.OrderDataGridView.Margin = new System.Windows.Forms.Padding(2);
            this.OrderDataGridView.Name = "OrderDataGridView";
            this.OrderDataGridView.ReadOnly = true;
            this.OrderDataGridView.RowHeadersVisible = false;
            this.OrderDataGridView.RowHeadersWidth = 62;
            this.OrderDataGridView.RowTemplate.Height = 28;
            this.OrderDataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.OrderDataGridView.Size = new System.Drawing.Size(631, 338);
            this.OrderDataGridView.TabIndex = 9;
            // 
            // AddButton
            // 
            this.AddButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.AddButton.Enabled = false;
            this.AddButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AddButton.Location = new System.Drawing.Point(468, 97);
            this.AddButton.Margin = new System.Windows.Forms.Padding(2);
            this.AddButton.Name = "AddButton";
            this.AddButton.Size = new System.Drawing.Size(91, 32);
            this.AddButton.TabIndex = 6;
            this.AddButton.Text = "Agregar";
            this.AddButton.UseVisualStyleBackColor = true;
            this.AddButton.Click += new System.EventHandler(this.Agregar_Click);
            // 
            // EraseButton
            // 
            this.EraseButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.EraseButton.Enabled = false;
            this.EraseButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EraseButton.Location = new System.Drawing.Point(578, 97);
            this.EraseButton.Margin = new System.Windows.Forms.Padding(2);
            this.EraseButton.Name = "EraseButton";
            this.EraseButton.Size = new System.Drawing.Size(91, 32);
            this.EraseButton.TabIndex = 7;
            this.EraseButton.Text = "Eliminar";
            this.EraseButton.UseVisualStyleBackColor = true;
            this.EraseButton.Click += new System.EventHandler(this.Eliminar_Click);
            // 
            // SerialPort
            // 
            this.SerialPort.PortName = "COM3";
            this.SerialPort.ReadTimeout = 500;
            this.SerialPort.WriteTimeout = 500;
            this.SerialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort_DataReceived);
            // 
            // WireOrderPanel
            // 
            this.WireOrderPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.WireOrderPanel.Controls.Add(this.ReelLabel);
            this.WireOrderPanel.Controls.Add(this.PeelingLength);
            this.WireOrderPanel.Controls.Add(this.Length);
            this.WireOrderPanel.Controls.Add(this.PrintButton);
            this.WireOrderPanel.Controls.Add(this.OrderDataGridView);
            this.WireOrderPanel.Controls.Add(this.Amount);
            this.WireOrderPanel.Controls.Add(this.EraseButton);
            this.WireOrderPanel.Controls.Add(this.label2);
            this.WireOrderPanel.Controls.Add(this.AddButton);
            this.WireOrderPanel.Controls.Add(this.label3);
            this.WireOrderPanel.Controls.Add(this.label4);
            this.WireOrderPanel.Controls.Add(this.Title);
            this.WireOrderPanel.Location = new System.Drawing.Point(-10, 12);
            this.WireOrderPanel.Name = "WireOrderPanel";
            this.WireOrderPanel.Size = new System.Drawing.Size(705, 561);
            this.WireOrderPanel.TabIndex = 14;
            this.WireOrderPanel.Visible = false;
            // 
            // ReelLabel
            // 
            this.ReelLabel.AutoSize = true;
            this.ReelLabel.BackColor = System.Drawing.Color.Transparent;
            this.ReelLabel.Font = new System.Drawing.Font("Arial", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReelLabel.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ReelLabel.Location = new System.Drawing.Point(461, 15);
            this.ReelLabel.Name = "ReelLabel";
            this.ReelLabel.Size = new System.Drawing.Size(112, 40);
            this.ReelLabel.TabIndex = 11;
            this.ReelLabel.Text = "10000";
            this.ReelLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // PeelingLength
            // 
            this.PeelingLength.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.PeelingLength.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PeelingLength.Location = new System.Drawing.Point(187, 101);
            this.PeelingLength.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.PeelingLength.Name = "PeelingLength";
            this.PeelingLength.Size = new System.Drawing.Size(96, 29);
            this.PeelingLength.TabIndex = 5;
            this.PeelingLength.Click += new System.EventHandler(this.PeelingLength_Click);
            // 
            // Length
            // 
            this.Length.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.Length.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Length.Location = new System.Drawing.Point(49, 101);
            this.Length.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.Length.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.Length.Name = "Length";
            this.Length.Size = new System.Drawing.Size(96, 29);
            this.Length.TabIndex = 4;
            this.Length.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.Length.Click += new System.EventHandler(this.Length_Click);
            // 
            // Amount
            // 
            this.Amount.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.Amount.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Amount.Location = new System.Drawing.Point(328, 100);
            this.Amount.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Amount.Name = "Amount";
            this.Amount.Size = new System.Drawing.Size(96, 29);
            this.Amount.TabIndex = 3;
            this.Amount.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Amount.Click += new System.EventHandler(this.Amount_Click);
            // 
            // ConectionTimer
            // 
            this.ConectionTimer.Interval = 1000;
            this.ConectionTimer.Tick += new System.EventHandler(this.ConectionTimer_Tick);
            // 
            // ConectionPanel
            // 
            this.ConectionPanel.Controls.Add(this.ConectionButton);
            this.ConectionPanel.Controls.Add(this.ConectionProgressBar);
            this.ConectionPanel.Controls.Add(this.ConectionTitle);
            this.ConectionPanel.Location = new System.Drawing.Point(5, 12);
            this.ConectionPanel.Name = "ConectionPanel";
            this.ConectionPanel.Size = new System.Drawing.Size(674, 561);
            this.ConectionPanel.TabIndex = 15;
            // 
            // ConectionButton
            // 
            this.ConectionButton.Location = new System.Drawing.Point(258, 341);
            this.ConectionButton.Name = "ConectionButton";
            this.ConectionButton.Size = new System.Drawing.Size(173, 39);
            this.ConectionButton.TabIndex = 3;
            this.ConectionButton.Text = "Conectar";
            this.ConectionButton.UseVisualStyleBackColor = true;
            this.ConectionButton.Click += new System.EventHandler(this.ConectionButton_Click);
            // 
            // ConectionProgressBar
            // 
            this.ConectionProgressBar.Location = new System.Drawing.Point(172, 235);
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
            this.ConectionTitle.Location = new System.Drawing.Point(260, 134);
            this.ConectionTitle.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.ConectionTitle.Name = "ConectionTitle";
            this.ConectionTitle.Size = new System.Drawing.Size(171, 45);
            this.ConectionTitle.TabIndex = 1;
            this.ConectionTitle.Text = "Conexion";
            // 
            // OrderTimer
            // 
            this.OrderTimer.Interval = 500;
            this.OrderTimer.Tick += new System.EventHandler(this.OrderTimer_Tick);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(684, 576);
            this.Controls.Add(this.WireOrderPanel);
            this.Controls.Add(this.ConectionPanel);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MinimumSize = new System.Drawing.Size(700, 615);
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = " Wire-Trimmer";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Main_FormClosed);
            this.Load += new System.EventHandler(this.Main_Load);
            ((System.ComponentModel.ISupportInitialize)(this.OrderDataGridView)).EndInit();
            this.WireOrderPanel.ResumeLayout(false);
            this.WireOrderPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PeelingLength)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Length)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Amount)).EndInit();
            this.ConectionPanel.ResumeLayout(false);
            this.ConectionPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label Title;
        private System.Windows.Forms.Button PrintButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.DataGridView OrderDataGridView;
        private System.Windows.Forms.Button AddButton;
        private System.Windows.Forms.Button EraseButton;
        private System.IO.Ports.SerialPort SerialPort;
        private System.Windows.Forms.Panel WireOrderPanel;
        private System.Windows.Forms.NumericUpDown Amount;
        private System.Windows.Forms.NumericUpDown PeelingLength;
        private System.Windows.Forms.NumericUpDown Length;
        private System.Windows.Forms.Timer ConectionTimer;
        private System.Windows.Forms.Panel ConectionPanel;
        private System.Windows.Forms.Button ConectionButton;
        private System.Windows.Forms.ProgressBar ConectionProgressBar;
        private System.Windows.Forms.Label ConectionTitle;
        private System.Windows.Forms.Label ReelLabel;
        private System.Windows.Forms.Timer OrderTimer;
    }
}

