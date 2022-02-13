import {Component, OnInit} from '@angular/core';
import {Board} from "../../lib/data-access/models/board";
import {List} from "../../lib/data-access/models/list";

@Component({
    selector: 'app-board',
    templateUrl: './board.component.html',
    styleUrls: ['./board.component.scss']
})
export class BoardComponent implements OnInit {

    board: Board;
    currentList: List;

    constructor() {
    }

    ngOnInit(): void {
        this.dummyData();
        this.currentList = this.board.lists[0];
    }

    dummyData(): void {
        //this.board = {"", [{1, "stuff", []}, {2, "stuff2", []}]};
        this.board = {title: "test",
            lists: [{id: 1, title: "stuff", reminders: [{id: 1, title: "r1", date: "31-12-2001"}, {id: 2, title: "r2", date: "31-12-2005"}]}, {
                id: 2,
                title: "stuff2",
                reminders: [{id: 1, title: "r1", date: "31-12-2002"}, {id: 2, title: "r2", date: "31-12-2003"}]
            }]
        };
    }

}
