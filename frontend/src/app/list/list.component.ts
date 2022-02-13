import {Component, Input, OnInit} from '@angular/core';
import {List} from "../../lib/data-access/models/list";

@Component({
  selector: 'app-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss']
})
export class ListComponent implements OnInit {

  @Input()
  list : List;

  constructor() { }

  ngOnInit(): void {
  }

}
