import {AfterViewInit, Component, ElementRef, EventEmitter, Input, OnInit, Output, ViewChild} from '@angular/core';
import {Reminder} from "../../lib/data-access/models/reminder";

@Component({
  selector: 'app-reminder',
  templateUrl: './reminder.component.html',
  styleUrls: ['./reminder.component.scss']
})
export class ReminderComponent implements OnInit, AfterViewInit {

  @Input()
  reminder : Reminder;

  @Output()
  deleteClicked: EventEmitter<Reminder> = new EventEmitter<Reminder>();

  @ViewChild('title')
  inputField : ElementRef;

  constructor() { }

  ngOnInit(): void {
  }

  ngAfterViewInit() {
    this.inputField.nativeElement.focus();
  }

  onDeleteClicked(){
    this.deleteClicked.emit(this.reminder);
  }
}
