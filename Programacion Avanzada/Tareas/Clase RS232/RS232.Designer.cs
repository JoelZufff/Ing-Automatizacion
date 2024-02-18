namespace Clase_RS232
{
    partial class RS232
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
            this.comboBox_SP = new System.Windows.Forms.ComboBox();
            this.Button_Search = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.SuspendLayout();
            // 
            // comboBox_SP
            // 
            this.comboBox_SP.FormattingEnabled = true;
            this.comboBox_SP.Location = new System.Drawing.Point(248, 146);
            this.comboBox_SP.Name = "comboBox_SP";
            this.comboBox_SP.Size = new System.Drawing.Size(121, 21);
            this.comboBox_SP.TabIndex = 0;
            // 
            // Button_Search
            // 
            this.Button_Search.Location = new System.Drawing.Point(403, 144);
            this.Button_Search.Name = "Button_Search";
            this.Button_Search.Size = new System.Drawing.Size(75, 23);
            this.Button_Search.TabIndex = 1;
            this.Button_Search.Text = "Search";
            this.Button_Search.UseVisualStyleBackColor = true;
            this.Button_Search.Click += new System.EventHandler(this.Button_Search_Click);
            // 
            // RS232
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.Button_Search);
            this.Controls.Add(this.comboBox_SP);
            this.Name = "RS232";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.RS232_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox_SP;
        private System.Windows.Forms.Button Button_Search;
        private System.IO.Ports.SerialPort serialPort1;
    }
}

