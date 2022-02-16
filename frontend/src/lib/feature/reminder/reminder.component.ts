import {AfterViewInit, Component, ElementRef, EventEmitter, Input, OnInit, Output, ViewChild} from '@angular/core';
import {Reminder} from "../../data-access/models/reminder";

@Component({
  selector: 'reminder',
  templateUrl: './reminder.component.html',
  styleUrls: ['./reminder.component.scss']
})
export class ReminderComponent implements OnInit, AfterViewInit {

  @Input()
  reminder : Reminder;
  date : string;
  deleteTimer: number = -1;

  @Output()
  updateEvent: EventEmitter<Reminder> = new EventEmitter<Reminder>();

  @Output()
  deleteEvent: EventEmitter<{reminder: Reminder, type: string}> = new EventEmitter<{reminder: Reminder, type: string}>();

  @ViewChild('title')
  inputField : ElementRef;

  @ViewChild('flag')
  flagImg : ElementRef;

  @ViewChild('flagbtn')
  flagIBtn : ElementRef;

  @ViewChild('date')
  inputDate : ElementRef;

  constructor() { }

  ngOnInit(): void {
  }

  ngAfterViewInit() {
    this.inputField.nativeElement.focus();
    this.setFlagIcon();
  }

  toggleFlag() {
    this.reminder.flagged = !this.reminder.flagged;
    this.setFlagIcon();
    this.triggerUpdate();
  }

  setFlagIcon(){
    if(this.reminder.flagged) {
      this.flagImg.nativeElement.setAttribute("src", "/assets/pics/markTrue.png");
      this.flagIBtn.nativeElement.setAttribute("class", "reminder-button flag true");
    }
    else {
      this.flagImg.nativeElement.setAttribute("src", "/assets/pics/markFalse.png");
      this.flagIBtn.nativeElement.setAttribute("class", "reminder-button flag false");
    }
  }

  triggerUpdate(){
    this.updateEvent.emit(this.reminder);
  }

  triggerDelete(){
    if(this.deleteTimer === -1){
      this.deleteEvent.emit({reminder: this.reminder, type: "countdown"});
      this.deleteTimer = 3;
      let interval = setInterval(()=>{
        if(this.deleteTimer === 1){
          clearInterval(interval);
          this.deleteEvent.emit({reminder: this.reminder, type: "delete"});
        }
        else if(this.deleteTimer === -1){
          clearInterval(interval);
          this.deleteEvent.emit({reminder: this.reminder, type: "cancel"});
        }
        else {
          this.deleteTimer--;
        }
      }, 1000);
    }
    else {
      this.deleteTimer = -1;
    }
  }


}
