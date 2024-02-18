namespace Sistema_Almacen
{
    partial class AdminLogin
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.TextBoxPswd = new System.Windows.Forms.TextBox();
            this.TitlePswd = new System.Windows.Forms.Label();
            this.SendButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // TextBoxPswd
            // 
            this.TextBoxPswd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.TextBoxPswd.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextBoxPswd.Location = new System.Drawing.Point(72, 114);
            this.TextBoxPswd.Name = "TextBoxPswd";
            this.TextBoxPswd.Size = new System.Drawing.Size(252, 29);
            this.TextBoxPswd.TabIndex = 1;
            this.TextBoxPswd.UseSystemPasswordChar = true;
            this.TextBoxPswd.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBoxPswd_KeyPress);
            // 
            // TitlePswd
            // 
            this.TitlePswd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.TitlePswd.AutoSize = true;
            this.TitlePswd.Font = new System.Drawing.Font("Franklin Gothic Medium Cond", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TitlePswd.Location = new System.Drawing.Point(88, 47);
            this.TitlePswd.Name = "TitlePswd";
            this.TitlePswd.Size = new System.Drawing.Size(221, 37);
            this.TitlePswd.TabIndex = 2;
            this.TitlePswd.Text = "CLAVE DE INGRESO";
            // 
            // SendButton
            // 
            this.SendButton.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.SendButton.Font = new System.Drawing.Font("Franklin Gothic Book", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SendButton.Location = new System.Drawing.Point(140, 181);
            this.SendButton.Name = "SendButton";
            this.SendButton.Size = new System.Drawing.Size(107, 42);
            this.SendButton.TabIndex = 3;
            this.SendButton.Text = "Enviar";
            this.SendButton.UseVisualStyleBackColor = true;
            this.SendButton.Click += new System.EventHandler(this.SendButton_Click);
            // 
            // AdminLogin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(384, 261);
            this.Controls.Add(this.SendButton);
            this.Controls.Add(this.TitlePswd);
            this.Controls.Add(this.TextBoxPswd);
            this.MaximumSize = new System.Drawing.Size(400, 300);
            this.MinimumSize = new System.Drawing.Size(400, 300);
            this.Name = "AdminLogin";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Administrador";
            this.Load += new System.EventHandler(this.Administrador_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox TextBoxPswd;
        private System.Windows.Forms.Label TitlePswd;
        private System.Windows.Forms.Button SendButton;
    }
}