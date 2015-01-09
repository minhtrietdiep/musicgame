namespace MusicGameServer
{
    partial class MusicGameForm
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
            this.components = new System.ComponentModel.Container();
            this.readMessageTimer = new System.Windows.Forms.Timer(this.components);
            this.musicSelectionBox = new System.Windows.Forms.ComboBox();
            this.setMusicButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // readMessageTimer
            // 
            this.readMessageTimer.Tick += new System.EventHandler(this.readMessageTimer_Tick);
            // 
            // musicSelectionBox
            // 
            this.musicSelectionBox.FormattingEnabled = true;
            this.musicSelectionBox.Location = new System.Drawing.Point(12, 35);
            this.musicSelectionBox.Name = "musicSelectionBox";
            this.musicSelectionBox.Size = new System.Drawing.Size(121, 21);
            this.musicSelectionBox.TabIndex = 0;
            // 
            // setMusicButton
            // 
            this.setMusicButton.Location = new System.Drawing.Point(13, 63);
            this.setMusicButton.Name = "setMusicButton";
            this.setMusicButton.Size = new System.Drawing.Size(75, 23);
            this.setMusicButton.TabIndex = 1;
            this.setMusicButton.Text = "Set Music";
            this.setMusicButton.UseVisualStyleBackColor = true;
            // 
            // MusicGameForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.setMusicButton);
            this.Controls.Add(this.musicSelectionBox);
            this.Name = "MusicGameForm";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MusicGameForm_FormClosed);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer readMessageTimer;
        private System.Windows.Forms.ComboBox musicSelectionBox;
        private System.Windows.Forms.Button setMusicButton;
    }
}

